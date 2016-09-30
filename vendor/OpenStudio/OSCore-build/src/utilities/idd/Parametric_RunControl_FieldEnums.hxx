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

#ifndef UTILITIES_IDD_PARAMETRIC_RUNCONTROL_FIELDENUMS_HXX
#define UTILITIES_IDD_PARAMETRIC_RUNCONTROL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Parametric_RunControlFields
 *  \brief Enumeration of Parametric:RunControl's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Parametric_RunControlFields, )
#else
class Parametric_RunControlFields: public ::EnumBase<Parametric_RunControlFields> {
 public: 
  enum domain 
  {
Name,   };
  Parametric_RunControlFields()
   : EnumBase<Parametric_RunControlFields>(Name) {} 
  Parametric_RunControlFields(const std::string &t_name) 
   : EnumBase<Parametric_RunControlFields>(t_name) {} 
  Parametric_RunControlFields(int t_value) 
   : EnumBase<Parametric_RunControlFields>(t_value) {} 
  static std::string enumName() 
  { return "Parametric_RunControlFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Parametric_RunControlFields>::value()); }
   private:
    friend class EnumBase<Parametric_RunControlFields>;
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
{ Parametric_RunControlFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Parametric_RunControlFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Parametric_RunControlFields> OptionalParametric_RunControlFields ;
#endif

/** \class Parametric_RunControlExtensibleFields
 *  \brief Enumeration of Parametric:RunControl's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Parametric_RunControlExtensibleFields, )
#else
class Parametric_RunControlExtensibleFields: public ::EnumBase<Parametric_RunControlExtensibleFields> {
 public: 
  enum domain 
  {
PerformRun,   };
  Parametric_RunControlExtensibleFields()
   : EnumBase<Parametric_RunControlExtensibleFields>(PerformRun) {} 
  Parametric_RunControlExtensibleFields(const std::string &t_name) 
   : EnumBase<Parametric_RunControlExtensibleFields>(t_name) {} 
  Parametric_RunControlExtensibleFields(int t_value) 
   : EnumBase<Parametric_RunControlExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Parametric_RunControlExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Parametric_RunControlExtensibleFields>::value()); }
   private:
    friend class EnumBase<Parametric_RunControlExtensibleFields>;
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
{ Parametric_RunControlExtensibleFields::PerformRun, "PerformRun", "Perform Run"},
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
  inline std::ostream &operator<<(std::ostream &os, const Parametric_RunControlExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Parametric_RunControlExtensibleFields> OptionalParametric_RunControlExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PARAMETRIC_RUNCONTROL_FIELDENUMS_HXX
