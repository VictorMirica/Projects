#version 330

// Input
in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;

uniform bool mix_t;
uniform float move_y;
uniform float move_x;
uniform bool is_ground;

uniform vec3 directional_light_pos;
uniform vec3 directional_light_color;

uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// Output
layout(location = 0) out vec4 out_color;


vec3 point_light_contribution(vec3 light_position, vec3 light_color)
{
    vec3 L = normalize( light_position - world_position );
    vec3 V = normalize( eye_position - world_position );
    vec3 H = normalize( L + V );
    vec3 R = normalize(reflect(-L, world_normal));

    float ambient_light = material_kd * 0.5f;
    float diffuse_light = material_kd * 100.f * max(dot(world_normal, L), 0);

    int primesteLumina;
    if (diffuse_light > 0)
    {
        primesteLumina = 1;
    } else {
        primesteLumina = 0;
    }

    float specular_light = material_ks * 100.f  * primesteLumina *  pow(max(dot(V, R), 0), material_shininess);
    float light_att_factor = 1 / (pow(distance(light_position, world_position), 2) + 1);

    float culoareObiect = ambient_light + light_att_factor * (diffuse_light + specular_light);

    return (culoareObiect * light_color);
}

void main()
{
    vec2 textCoord = texcoord;
    if (is_ground) { // Misc textura planului
        textCoord.y += move_y * 0.03f;
        textCoord.x -= move_x * 0.02f;
    }

    vec4 color1 = texture(texture_1, textCoord);
    vec4 color2 = texture(texture_2, textCoord);

    // In cazul in care vreau sa combin doua texturi
      if (mix_t) {
        out_color = mix(color1, color2, 0.8f);
    } else {
        out_color = color1;
    }

    vec3 color = point_light_contribution(directional_light_pos, directional_light_color);
   
    out_color *= vec4(color, 1);

    if (out_color.a < 0.5f) {
        discard;
    }
}
