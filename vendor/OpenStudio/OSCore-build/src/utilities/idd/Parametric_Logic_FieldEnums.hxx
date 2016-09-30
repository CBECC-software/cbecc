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

#ifndef UTILITIES_IDD_PARAMETRIC_LOGIC_FIELDENUMS_HXX
#define UTILITIES_IDD_PARAMETRIC_LOGIC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Parametric_LogicFields
 *  \brief Enumeration of Parametric:Logic's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Parametric_LogicFields, )
#else
class Parametric_LogicFields: public ::EnumBase<Parametric_LogicFields> {
 public: 
  enum domain 
  {
Name,   };
  Parametric_LogicFields()
   : EnumBase<Parametric_LogicFields>(Name) {} 
  Parametric_LogicFields(const std::string &t_name) 
   : EnumBase<Parametric_LogicFields>(t_name) {} 
  Parametric_LogicFields(int t_value) 
   : EnumBase<Parametric_LogicFields>(t_value) {} 
  static std::string enumName() 
  { return "Parametric_LogicFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Parametric_LogicFields>::value()); }
   private:
    friend class EnumBase<Parametric_LogicFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ Parametric_LogicFields::Name, "Name", "Name"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const Parametric_LogicFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Parametric_LogicFields> OptionalParametric_LogicFields ;
#endif

/** \class Parametric_LogicExtensibleFields
 *  \brief Enumeration of Parametric:Logic's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Parametric_LogicExtensibleFields, )
#else
class Parametric_LogicExtensibleFields: public ::EnumBase<Parametric_LogicExtensibleFields> {
 public: 
  enum domain 
  {
ParametricLogicLine,   };
  Parametric_LogicExtensibleFields()
   : EnumBase<Parametric_LogicExtensibleFields>(ParametricLogicLine) {} 
  Parametric_LogicExtensibleFields(const std::string &t_name) 
   : EnumBase<Parametric_LogicExtensibleFields>(t_name) {} 
  Parametric_LogicExtensibleFields(int t_value) 
   : EnumBase<Parametric_LogicExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Parametric_LogicExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Parametric_LogicExtensibleFields>::value()); }
   private:
    friend class EnumBase<Parametric_LogicExtensibleFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ Parametric_LogicExtensibleFields::ParametricLogicLine, "ParametricLogicLine", "Parametric Logic Line"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const Parametric_LogicExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Parametric_LogicExtensibleFields> OptionalParametric_LogicExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PARAMETRIC_LOGIC_FIELDENUMS_HXX
