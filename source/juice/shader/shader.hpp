#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "core/utils.hpp"

namespace juice {

	enum class ShaderDataType
	{
		Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static std::uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch(type)
		{
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;	
			case ShaderDataType::Float3:	return 4 * 3;	
			case ShaderDataType::Float4:	return 4 * 4;	
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;
		}

		ASSERT(false, "Unknown Shader Data Type, ValidTypes: (Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool)");
	}

	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch(type)
		{
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}
		ASSERT(false, "Unknown Shader Data Type, ValidTypes: (Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool)");
	}

	struct BufferElement
	{
        std::string Name;
		ShaderDataType Type;
        std::uint32_t Size;
        std::uint32_t Offset;
		bool Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

        std::uint32_t GetComponentCount() const
		{
			switch(Type)
			{
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;
				case ShaderDataType::Mat3:		return 3 * 3;
				case ShaderDataType::Mat4:		return 4 * 4;
				case ShaderDataType::Int:		return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;
				case ShaderDataType::Bool:		return 1;
			}

			return 0;
		}

	};

	class Shader
	{
	public:
		Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetInt(const std::string& name, int value);
		void SetIntArray(const std::string& name, int* values, int count);
		void SetFloat(const std::string& name, float value);
		void SetFloat2(const std::string& name, const glm::vec2& value);
		void SetFloat3(const std::string& name, const glm::vec3& value);
		void SetFloat4(const std::string& name, const glm::vec4& value);
		void SetMat4(const std::string& name, const glm::mat4& value);

		const std::string& GetName() const { return m_Name; };
	
	private:
		GLuint m_ShaderID;
		std::string m_Name;

	private:
		void Load(const std::string& vertexSrc, const std::string& fragmentSrc);
		void CompileShader(const char* VertexSourcePointer, const char* FragmentSourcePointer);
		void CreateProgram(GLuint VertexShaderID, GLuint FragmentShaderID);
		void DeleteShader(GLuint ProgramID, GLuint VertexShaderID, GLuint FragmentShaderID);

		void ShaderErr(std::string desc, GLuint ShaderSourceID);

		GLint getUniformLocation(const GLchar* name);
	};

}
