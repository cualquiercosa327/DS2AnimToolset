//----------------------------------------------------------------------------------------------------------------------
/// \file Locator.cpp
/// \note (C) Copyright 2003-2005 Robert Bateman. All rights reserved.
//----------------------------------------------------------------------------------------------------------------------

#include "XMD/Locator.h"
#include "XMD/FileIO.h"

namespace XMD
{
//----------------------------------------------------------------------------------------------------------------------
XLocator::XLocator(XModel* pmod) 
  : XShape(pmod)
{
}

//----------------------------------------------------------------------------------------------------------------------
XLocator::~XLocator(void)
{
}

//----------------------------------------------------------------------------------------------------------------------
XFn::Type XLocator::GetApiType() const
{
  return XFn::Locator;
}

//----------------------------------------------------------------------------------------------------------------------
XBase* XLocator::GetFn(XFn::Type type)
{
  if(XFn::Locator==type)
    return (XLocator*)this;
  return XShape::GetFn(type);
}

//----------------------------------------------------------------------------------------------------------------------
const XBase* XLocator::GetFn(XFn::Type type) const
{
  if(XFn::Locator==type)
    return (const XLocator*)this;
  return XShape::GetFn(type);
}

//----------------------------------------------------------------------------------------------------------------------
bool XLocator::WriteChunk(std::ostream& ofs)
{
  return ofs.good();
}

//----------------------------------------------------------------------------------------------------------------------
bool XLocator::DoData(XFileIO& io)
{
  DUMPER(XLocator);

  IO_CHECK( XShape::DoData(io) );

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
XMD::XU32 XLocator::GetDataSize() const
{
  return XShape::GetDataSize();
}

//----------------------------------------------------------------------------------------------------------------------
bool XLocator::ReadChunk(std::istream& ifs)
{
  return ifs.good();
}

//----------------------------------------------------------------------------------------------------------------------
void XLocator::PreDelete(XIdSet& extra_nodes)
{
  XShape::PreDelete(extra_nodes);
}

//----------------------------------------------------------------------------------------------------------------------
bool XLocator::NodeDeath(XId id)
{
  return XShape::NodeDeath(id);
}

//----------------------------------------------------------------------------------------------------------------------
void XLocator::DoCopy(const XBase* rhs)
{
  const XLocator* cb = rhs->HasFn<XLocator>();
  XMD_ASSERT(cb);
  XShape::DoCopy(cb);
}
}
