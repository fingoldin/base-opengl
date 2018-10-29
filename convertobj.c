#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char * argv[])
{
    if(argc != 3) {
        printf("invalid number of arguments given!\n");
        return 1;
    }
    
    int data_file_name_length = 99;
    if(strlen(argv[2]) > data_file_name_length - 6) {
        printf("data file name is too long!\n");
        return 1;
    }
    
    char * obj_file_name = argv[1];
    
    char data_file_name[data_file_name_length + 1];
    sprintf(data_file_name, "%sdata.h", argv[2]);
    
    FILE * obj_file = fopen(obj_file_name, "r");
    FILE * data_file = fopen(data_file_name, "w");
    if(obj_file == NULL || data_file == NULL) {
        printf("Error opening files!\n");
        return 1;
    }
    
    const int line_length = 100;
    char line[line_length];
    
    long int num_positions, num_normals, num_UVs, num_faces, positions_index, normals_index, UVs_index, faces_index, paths_index;
    
    int name_len = strlen(argv[2]);
    char capital[name_len + 1];
    
    for(int i = 0; i < name_len; i++)
        capital[i] = toupper(*(argv[2]+ i));
    capital[name_len] = '\0';
    
    fprintf(data_file, "#ifndef %s_DATA_H\n", capital);
    fprintf(data_file, "#define %s_DATA_H\n", capital);
    fprintf(data_file, "#include <stdlib.h>\n#include <string>\n#include <vector>\n#include <GL/glew.h>\n\n");
    
    fprintf(data_file, "GLfloat %s_positions[] = {\n", argv[2]);
    positions_index = ftell(data_file);
    fprintf(data_file, "\n};\n\nGLfloat %s_normals[] = {\n", argv[2]);
    normals_index = ftell(data_file);
    fprintf(data_file, "\n};\n\nGLfloat %s_UVs[] = {\n", argv[2]);
    UVs_index = ftell(data_file);
    fprintf(data_file, "\n};\n\nGLuint %s_indices[] = {\n", argv[2]);
    faces_index = ftell(data_file);
    fprintf(data_file, "\n};\n\nstd::vector<std::string> %s_tex_paths { ", argv[2]);
    paths_index = ftell(data_file);
    fprintf(data_file, "};");
    
    char v[3], x[15], y[15], z[15];
    
    char use[] = "usemtl";
    const int use_len = strlen(use);
    char sub[use_len+1];
    
    int texture = 0;
    const int max_textures = 16;
    int num_textures = 0;
    const int max_texture_name_len = 49;
    char textures[max_textures][max_texture_name_len+1];
    
    while(fgets(line, line_length, obj_file) != NULL)
    {
        memcpy(sub, line, use_len * sizeof(char));
        sub[use_len] = '\0';
        int line_len = strlen(line);
        
        if(line[0] == 'v') {
            if(line[1] == ' ') {
                sscanf(line, "%s %s %s %s", v, x, y, z);
                fseek(data_file, positions_index, SEEK_SET);
                fprintf(data_file, "    %s, %s, %s,\n", x, y, z);
                long int offset = ftell(data_file) - positions_index;
                positions_index += offset;
                normals_index += offset;
                UVs_index += offset;
                faces_index += offset;
                paths_index += offset;
                num_positions++;
            }
            else if(line[1] == 'n') {
                sscanf(line, "%s %s %s %s", v, x, y, z);
                fseek(data_file, normals_index, SEEK_SET);
                fprintf(data_file, "    %s, %s, %s,\n", x, y, z);
                long int offset = ftell(data_file) - normals_index;
                normals_index += offset;
                UVs_index += offset;
                faces_index += offset;
                paths_index += offset;
                num_normals++;
            }
            else if(line[1] == 't') {
                sscanf(line, "%s %s %s", v, x, y);
                fseek(data_file, UVs_index, SEEK_SET);
                fprintf(data_file, "    %s, %s,\n", x, y);
                long int offset = ftell(data_file) - UVs_index;
                UVs_index += offset;
                faces_index += offset;
                paths_index += offset;
                num_UVs++;
            }
        }
        else if(line[0] == 'f') {
            long int v1, n1, t1, v2, n2, t2, v3, n3, t3;
            if(num_UVs == 0) {
                if(num_normals == 0) {
                    sscanf(line, "%s %ld %ld %ld", v, &v1, &v2, &v3);
                }
                else {
                    sscanf(line, "%s %ld//%ld %ld//%ld %ld//%ld", v, &v1, &n1, &v2, &n2, &v3, &n3);
                }
            }
            else {
                sscanf(line, "%s %ld/%ld/%ld %ld/%ld/%ld %ld/%ld/%ld", v, &v1, &n1, &t1, &v2, &n2, &t2, &v3, &n3, &t3);
            }
            fseek(data_file, faces_index, SEEK_SET);
            fprintf(data_file, "    %ld, %ld, %ld, %d,\n    %ld, %ld %ld, %d,\n    %ld, %ld, %ld, %d,\n", v1, n1, t1, texture, v2, n2, t2, texture, v3, n3, t3, texture);
            long int offset = ftell(data_file) - faces_index;
            faces_index += offset;
            paths_index += offset;
            num_faces++;
        }
        else if(strcmp(sub, use) == 0) {
            int used = 0;
            for(int i = 0; i < num_textures; i++) {
                if(strcmp(textures[i], (line + use_len + 1)) == 0) {
                    used = 1;
                    texture = i;
                    break;
                }
            }
            if(!used) {
                if(num_textures == max_textures) {
                    printf("Too many textures!\n");
                    return 1;
                }
                if(line_len-use_len-1 > max_texture_name_len) {
                    printf("texture name '%s' is too long\n", (line + use_len + 1));
                    return 1;
                }
                memcpy(textures[num_textures], (line + use_len + 1), (line_len - use_len - 1) * sizeof(char));
                textures[num_textures][line_len - use_len - 1] = '\0';
                texture = num_textures;
                fseek(data_file, paths_index, SEEK_SET);
                fprintf(data_file, "\"%s\" ", textures[num_textures]);
                paths_index = ftell(data_file);
                num_textures++;
            }
        }
    }
    
    return 0;
}
