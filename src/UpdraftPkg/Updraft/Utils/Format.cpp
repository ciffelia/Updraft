#include "Format.hpp"

char* Format()
{
  return Sprintf("");
}

char* Format(const int8 value)
{
  return Sprintf("%d", value);
}

char* Format(const int16 value)
{
  return Sprintf("%d", value);
}

char* Format(const int32 value)
{
  return Sprintf("%d", value);
}

char* Format(const int64 value)
{
  return Sprintf("%ld", value);
}

char* Format(const double value)
{
  return Sprintf("%g", value);
}

char* Format(const uint8 value)
{
  return Sprintf("%u", value);
}

char* Format(const uint16 value)
{
  return Sprintf("%u", value);
}

char* Format(const uint32 value)
{
  return Sprintf("%u", value);
}

char* Format(const uint64 value)
{
  return Sprintf("%lu", value);
}

char* Format(const CHAR8 *value)
{
  return Sprintf("%s", value);
}

char* Format(const CHAR16 *value)
{
  const uintn bufSize = ::StrLen(value);
  char *buf = new char[bufSize];
  ::UnicodeStrToAsciiStr(value, buf);

  return buf;
}

char* Format(const bool value)
{
  return Format(value ? "true" : "false");
}

char* Format(const PrintEfiStatus value)
{
  switch (value.m_returnStatus)
  {
    case RETURN_SUCCESS:
      return Format("Success");
    case RETURN_LOAD_ERROR:
      return Format("Load Error");
    case RETURN_INVALID_PARAMETER:
      return Format("Invalid Parameter");
    case RETURN_UNSUPPORTED:
      return Format("Unsupported");
    case RETURN_BAD_BUFFER_SIZE:
      return Format("Bad Buffer Size");
    case RETURN_BUFFER_TOO_SMALL:
      return Format("Buffer Too Small");
    case RETURN_NOT_READY:
      return Format("Not Ready");
    case RETURN_DEVICE_ERROR:
      return Format("Device Error");
    case RETURN_WRITE_PROTECTED:
      return Format("Write Protected");
    case RETURN_OUT_OF_RESOURCES:
      return Format("Out of Resources");
    case RETURN_VOLUME_CORRUPTED:
      return Format("Volume Corrupt");
    case RETURN_VOLUME_FULL:
      return Format("Volume Full");
    case RETURN_NO_MEDIA:
      return Format("No Media");
    case RETURN_MEDIA_CHANGED:
      return Format("Media changed");
    case RETURN_NOT_FOUND:
      return Format("Not Found");
    case RETURN_ACCESS_DENIED:
      return Format("Access Denied");
    case RETURN_NO_RESPONSE:
      return Format("No Response");
    case RETURN_NO_MAPPING:
      return Format("No mapping");
    case RETURN_TIMEOUT:
      return Format("Time out");
    case RETURN_NOT_STARTED:
      return Format("Not started");
    case RETURN_ALREADY_STARTED:
      return Format("Already started");
    case RETURN_ABORTED:
      return Format("Aborted");
    case RETURN_ICMP_ERROR:
      return Format("ICMP Error");
    case RETURN_TFTP_ERROR:
      return Format("TFTP Error");
    case RETURN_PROTOCOL_ERROR:
      return Format("Protocol Error");
    case RETURN_WARN_UNKNOWN_GLYPH:
      return Format("Warning Unknown Glyph");
    case RETURN_WARN_DELETE_FAILURE:
      return Format("Warning Delete Failure");
    case RETURN_WARN_WRITE_FAILURE:
      return Format("Warning Write Failure");
    case RETURN_WARN_BUFFER_TOO_SMALL:
      return Format("Warning Buffer Too Small");
  }
}

char* Format(const Vec2 value)
{
  return Format("(", value.x, ",", value.y, ")");
}

char* Format(const Circular value)
{
  return Format("(", value.r, ",", value.theta, ")");
}

char* Format(const Circle value)
{
  return Format("(", value.center.x, ",", value.center.y, ",", value.r, ")");
}

char* Format(const Color value)
{
  return Format("(", value.r, ",", value.g, ",", value.b, ",", value.a, ")");
}

char* Format(const Point value)
{
  return Format("(", value.x, ",", value.y, ")");
}

char* Format(const Rect value)
{
  return Format("(", value.pos.x, ",", value.pos.y, ",", value.size.width, ",", value.size.height, ")");
}

char* Format(const Line value)
{
  return Format("(", value.begin.x, ",", value.begin.y, ",", value.end.x, ",", value.end.y, ")");
}

char* Format(const Size value)
{
  return Format("(", value.width, ",", value.height, ")");
}
