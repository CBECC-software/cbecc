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

#ifndef UTILITIES_IDD_OS_CONNECTION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CONNECTION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ConnectionFields
 *  \brief Enumeration of OS:Connection's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ConnectionFields, )
#else
class OS_ConnectionFields: public ::EnumBase<OS_ConnectionFields> {
 public: 
  enum domain 
  {
Handle, Name, SourceObject, OutletPort, TargetObject, InletPort,   };
  OS_ConnectionFields()
   : EnumBase<OS_ConnectionFields>(Handle) {} 
  OS_ConnectionFields(const std::string &t_name) 
   : EnumBase<OS_ConnectionFields>(t_name) {} 
  OS_ConnectionFields(int t_value) 
   : EnumBase<OS_ConnectionFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ConnectionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ConnectionFields>::value()); }
   private:
    friend class EnumBase<OS_ConnectionFields>;
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
{ OS_ConnectionFields::Handle, "Handle", "Handle"},
{ OS_ConnectionFields::Name, "Name", "Name"},
{ OS_ConnectionFields::SourceObject, "SourceObject", "Source Object"},
{ OS_ConnectionFields::OutletPort, "OutletPort", "Outlet Port"},
{ OS_ConnectionFields::TargetObject, "TargetObject", "Target Object"},
{ OS_ConnectionFields::InletPort, "InletPort", "Inlet Port"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ConnectionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ConnectionFields> OptionalOS_ConnectionFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CONNECTION_FIELDENUMS_HXX
