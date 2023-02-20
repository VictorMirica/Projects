#include "transform.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* transform::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* transform::CreateCircle(const std::string& name,
    glm::vec3 center,
    float length,
    glm::vec3 color,
    bool fill)
{
        std::vector<VertexFormat> vertices;
        vertices.push_back(VertexFormat(center, color));

        const float PI = 3.1415926f;

        float increment = 2.0f * PI / 25;

        for (float currAngle = 0.0f; currAngle <= 2.0f * PI; currAngle += increment)
        {
            vertices.push_back(VertexFormat(glm::vec3(length * cos(currAngle) , length * sin(currAngle) , 0), color));
        }

        std::vector<unsigned int> indices;

        for (int i = 1; i < vertices.size() - 1; i++) {
            indices.push_back(i + 1);
            indices.push_back(0);
            indices.push_back(i);
        }

        indices.push_back(1);
        indices.push_back(0);
        indices.push_back(vertices.size() - 1);


        Mesh* circle = new Mesh(name);

        if (!fill) {
            circle->SetDrawMode(GL_LINE_LOOP);
        }

        circle->InitFromData(vertices, indices);
        return circle;

}

Mesh* transform::CreateTriangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length / 2, length, 0), color),
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}
