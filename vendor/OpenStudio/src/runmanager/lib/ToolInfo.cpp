/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.  
*  All rights reserved.
*  
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*  
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*  
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#include "ToolInfo.hpp"
#include <boost/thread.hpp>

namespace openstudio {
namespace runmanager {

  ToolVersion::ToolVersion()
  {
  }

  ToolVersion::ToolVersion(int t_major)
    : m_major(t_major)
  {
  }

  ToolVersion::ToolVersion(int t_major, int t_minor)
    : m_major(t_major), m_minor(t_minor)
  {
  }

  ToolVersion::ToolVersion(int t_major, int t_minor, int t_build)
    : m_major(t_major), m_minor(t_minor), m_build(t_build)
  {
  }

  ToolVersion::ToolVersion(int t_major, int t_minor, int t_build, std::string t_tag)
    : m_major(t_major), m_minor(t_minor), m_build(t_build), m_tag(std::move(t_tag))
  {
  }

  ToolVersion::ToolVersion(boost::optional<int> t_major, boost::optional<int> t_minor, boost::optional<int> t_build,
      boost::optional<std::string> t_tag)
    : m_major(std::move(t_major)), m_minor(std::move(t_minor)), m_build(std::move(t_build)), m_tag(std::move(t_tag))
  {
  }

  bool ToolVersion::empty() const
  {
    return !m_major && !m_minor && !m_build;
  }

  /// Operator overload for streaming ToolVersion to ostream
  RUNMANAGER_API std::ostream &operator<<(std::ostream &os, const ToolVersion &tv)
  {
    return (os << tv.toString());
  }

  ToolVersion ToolVersion::fromString(const std::string &t_val) 
  {
    boost::optional<int> major;
    boost::optional<int> minor;
    boost::optional<int> build;
    boost::optional<std::string> tag;

    std::vector<std::string> parts;
    boost::split(parts, t_val, boost::is_any_of("."), boost::algorithm::token_compress_on);

    if (parts.size() > 0 && parts[0] != "-")
    {
      major = atoi(parts[0].c_str());
    }

    if (parts.size() > 1 && parts[1] != "-")
    {
      minor = atoi(parts[1].c_str());
    }

    if (parts.size() > 2 && parts[2] != "-")
    {
      build = atoi(parts[2].c_str());
    }

    if (parts.size() > 3 && parts[3] != "-")
    {
      tag = parts[3];
    }

    return ToolVersion(major, minor, build, tag);
  }

  std::string ToolVersion::toString() const
  {
    std::stringstream ss;

    if (m_major)
    {
      ss << *m_major;
    } else {
      ss << "-";
    }

    ss << ".";

    if (m_minor)
    {
      ss << *m_minor;
    } else {
      ss << "-";
    }

    ss << ".";

    if (m_build)
    {
      ss << *m_build;
    } else {
      ss << "-";
    }

    ss << ".";

    if (m_tag)
    {
      ss << *m_tag;
    } else {
      ss << "-";
    }

    return ss.str();
  }

  bool ToolVersion::operator==(const ToolVersion &rhs) const
  {
    return m_major == rhs.m_major
      && m_minor == rhs.m_minor
      && m_build == rhs.m_build
      && m_tag == rhs.m_tag;
  }

  bool ToolVersion::operator<(const ToolVersion &rhs) const
  {
    return m_major < rhs.m_major
      || (m_major == rhs.m_major && m_minor < rhs.m_minor)
      || (m_major == rhs.m_major && m_minor == rhs.m_minor && m_build < rhs.m_build)
      || (m_major == rhs.m_major && m_minor == rhs.m_minor && m_build == rhs.m_build && m_tag < rhs.m_tag);
  }

  bool ToolVersion::matches(const ToolVersion &requirements) const
  {
    // Updated: if the version number of the Tools is not known - call it a match
    // The most specific version that matches any *set* value will be found first
    //
    // Tag, if specified, must be an exact match
    return (m_major == requirements.m_major || !requirements.m_major || !m_major)
        && (m_minor == requirements.m_minor || !requirements.m_minor || !m_minor)
        && (m_build == requirements.m_build || !requirements.m_build || !m_build)
        && (m_tag  == requirements.m_tag  || !requirements.m_tag);
  }

  boost::optional<int> ToolVersion::getMajor() const
  {
    return m_major;
  }

  boost::optional<int> ToolVersion::getMinor() const
  {
    return m_minor;
  }

  boost::optional<int> ToolVersion::getBuild() const
  {
    return m_build;
  }

  boost::optional<std::string> ToolVersion::getTag() const
  {
    return m_tag;
  }


  ToolInfo Tools::getLastByName(const std::string &t_name) const
  {
    return getLast(std::bind(&Tools::nameCompare, t_name, std::placeholders::_1));
  }

  Tools Tools::getAllByName(const std::string &t_name) const
  {
    return getAll(std::bind(&Tools::nameCompare, t_name, std::placeholders::_1));
  }

  ToolInfo Tools::getLastByVersion(const ToolVersion &t_version) const
  {
    return getLast(std::bind(&Tools::versionCompare, t_version, std::placeholders::_1));
  }

  Tools Tools::getAllByVersion(const ToolVersion &t_version) const
  {
    return getAll(std::bind(&Tools::versionCompare, t_version, std::placeholders::_1));
  }

}
}

