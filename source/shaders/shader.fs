#version 440

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    sampler2D diffuse_texture;
    sampler2D specular_texture;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;
uniform vec3 light_position;
uniform vec3 camera_position;

vec4 calc_ambient(Material material){
    return vec4(material.ambient, 1.0f);
}

vec4 calc_diffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 light_position){
    vec3 diffuse_light = normalize(light_position - vs_position);    
    float diffuse_intensity = clamp( dot(diffuse_light, vs_normal), 0, 1 );
    diffuse_light = material.diffuse * diffuse_intensity;

    return vec4(diffuse_light, 1.0f);
}

vec4 calc_specular(Material material, vec3 vs_position, vec3 vs_normal, vec3 light_position, vec3 camera_position){
    vec3 specular_light = normalize(vs_position - light_position);
    vec3 reflection_dir = normalize( reflect( specular_light, normalize(vs_normal) ) );
    vec3 camera         = normalize( camera_position - vs_position);
    float specular_intensity = pow(max(dot(camera, reflection_dir), 0), 30); 
    specular_light      = material.specular * specular_intensity * texture(material.specular_texture, vs_texcoord).rgb;

    return vec4(specular_light, 1.0f);
}

void main(){

    vec4 ambient_final  = calc_ambient(material);
    vec4 diffuse_final  = calc_diffuse(material, vs_position, vs_normal, light_position); 
    vec4 specular_final = calc_specular(material, vs_position, vs_normal, light_position, camera_position);

    // fs_color = texture(material.diffuse_texture, vs_texcoord) * (ambient_final + diffuse_final + specular_final) * vec4(vs_color, 1.0f); // textura + iluminação + cor do objeto
    fs_color = texture(material.diffuse_texture, vs_texcoord) * (ambient_final + diffuse_final + specular_final); // textura + iluminação
    // fs_color = (ambient_final + diffuse_final + specular_final) * vec4(vs_color, 1.0f); // iluminação e cor do objeto
    // fs_color = (ambient_final + diffuse_final + specular_final); // iluminação 
}