#include "pch.hpp"
#include "graphics.hpp"

namespace juice {

	//////////////////////////////////////
	//			Vertex Buffer			//
	//////////////////////////////////////

	VertexBuffer::VertexBuffer(float* data, std::uint32_t size)
		: m_Size(size)
	{
		glGenBuffers(1, &m_VertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//////////////////////////////////////
	//			Index Buffer			//
	//////////////////////////////////////

	IndexBuffer::IndexBuffer(unsigned short int* data, std::uint32_t count)
		: m_Count(count)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned short int), data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::IndexBuffer(std::uint32_t* data, std::uint32_t count)
		: m_Count(count) 
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(std::uint32_t), data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	//////////////////////////////////////
	//			Vertex Array			//
	//////////////////////////////////////

	VertexArray::VertexArray() 
	{
		glGenVertexArrays(1, &m_VertexArrayID);
		glBindVertexArray(m_VertexArrayID);
	}

	void VertexArray::Bind() const 
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void VertexArray::Unbind() const 
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(const ref<VertexBuffer>& vertexBuffer) 
	{
		ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_VertexArrayID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		for( const auto& element : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, 
				element.GetComponentCount(), 
				ShaderDataTypeToOpenGLType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, 
				vertexBuffer->GetLayout().GetStride(), 
				(const void*)element.Offset
			);

			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::SetIndexBuffer(const ref<IndexBuffer>& indexBuffer) 
	{
		glBindVertexArray(m_VertexArrayID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}
