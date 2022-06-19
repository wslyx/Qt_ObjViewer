#include "OpenGLMesh.h"
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>

class OpenGLMeshPrivate
{
public:
  OpenGLMeshPrivate();
  void drawArrays();
  typedef void (OpenGLMeshPrivate::*DrawMethodCB)();
  OpenGLMesh::OpenGLBufferList m_buffers;
  QOpenGLVertexArrayObject *m_vao;
  int m_count;
  GLenum m_mode;
  DrawMethodCB m_drawMethod;
};

///
#define P(c) c &p = *m_private
OpenGLMesh::OpenGLMesh(QObject *parent)
    : QObject(parent), m_private(new OpenGLMeshPrivate)
{

}

const OpenGLMesh::OpenGLBufferList &OpenGLMesh::getBuffers() const
{
  P(OpenGLMeshPrivate);
  return p.m_buffers;
}

QOpenGLVertexArrayObject *OpenGLMesh::vertexArrayObject()
{
  P(OpenGLMeshPrivate);
  if (!p.m_vao)
  {
    p.m_vao = new QOpenGLVertexArrayObject(this);
    p.m_vao->create();
  }
  return p.m_vao;
}

QOpenGLBuffer OpenGLMesh::createBuffer(QOpenGLBuffer::UsagePattern hint)
{
  P(OpenGLMeshPrivate);
  QOpenGLBuffer buffer;
  buffer.create();
  buffer.setUsagePattern(hint);
  p.m_buffers.push_back(buffer);
  return buffer;
}

void OpenGLMesh::setMode(OpenGLMesh::Options options)
{
  (void)options;
}

void OpenGLMesh::setDrawArrays(GLenum mode, int count)
{
  P(OpenGLMeshPrivate);
  p.m_mode = mode;
  p.m_count = count;
  p.m_drawMethod = &OpenGLMeshPrivate::drawArrays;
}

void OpenGLMesh::draw()
{
  P(OpenGLMeshPrivate);
  p.m_vao->bind();
  (p.*p.m_drawMethod)();
  p.m_vao->release();
}

OpenGLMeshPrivate::OpenGLMeshPrivate()
{
  m_vao = Q_NULLPTR;
}

void OpenGLMeshPrivate::drawArrays()
{
  QOpenGLFunctions *f = static_cast<QOpenGLFunctions*>(
              QOpenGLContext::currentContext()->functions());
  f->glDrawArrays(m_mode, 0, m_count);
}
