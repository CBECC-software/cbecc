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

#ifndef UTILITIES_IDD_OS_METER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_METER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_MeterFields
 *  \brief Enumeration of OS:Meter's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_MeterFields, )
#else
class OS_MeterFields: public ::EnumBase<OS_MeterFields> {
 public: 
  enum domain 
  {
Handle, Name, ReportingFrequency, MeterFileOnly, Cumulative,   };
  OS_MeterFields()
   : EnumBase<OS_MeterFields>(Handle) {} 
  OS_MeterFields(const std::string &t_name) 
   : EnumBase<OS_MeterFields>(t_name) {} 
  OS_MeterFields(int t_value) 
   : EnumBase<OS_MeterFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_MeterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_MeterFields>::value()); }
   private:
    friend class EnumBase<OS_MeterFields>;
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
{ OS_MeterFields::Handle, "Handle", "Handle"},
{ OS_MeterFields::Name, "Name", "Name"},
{ OS_MeterFields::ReportingFrequency, "ReportingFrequency", "Reporting Frequency"},
{ OS_MeterFields::MeterFileOnly, "MeterFileOnly", "Meter File Only"},
{ OS_MeterFields::Cumulative, "Cumulative", "Cumulative"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_MeterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_MeterFields> OptionalOS_MeterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_METER_FIELDENUMS_HXX
