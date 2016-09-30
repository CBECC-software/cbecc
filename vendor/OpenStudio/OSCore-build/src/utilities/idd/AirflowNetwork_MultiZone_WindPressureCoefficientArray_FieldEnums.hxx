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

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_WINDPRESSURECOEFFICIENTARRAY_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_WINDPRESSURECOEFFICIENTARRAY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields
 *  \brief Enumeration of AirflowNetwork:MultiZone:WindPressureCoefficientArray's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields, )
#else
class AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields: public ::EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields> {
 public: 
  enum domain 
  {
Name,   };
  AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields()
   : EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields>(Name) {} 
  AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields>(t_name) {} 
  AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields(int t_value) 
   : EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields>::value()); }
   private:
    friend class EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields>;
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
{ AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_MultiZone_WindPressureCoefficientArrayFields> OptionalAirflowNetwork_MultiZone_WindPressureCoefficientArrayFields ;
#endif

/** \class AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields
 *  \brief Enumeration of AirflowNetwork:MultiZone:WindPressureCoefficientArray's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields, )
#else
class AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields: public ::EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields> {
 public: 
  enum domain 
  {
WindDirection,   };
  AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields()
   : EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields>(WindDirection) {} 
  AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields>(t_name) {} 
  AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields(int t_value) 
   : EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields>::value()); }
   private:
    friend class EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields>;
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
{ AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields::WindDirection, "WindDirection", "Wind Direction"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields> OptionalAirflowNetwork_MultiZone_WindPressureCoefficientArrayExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_WINDPRESSURECOEFFICIENTARRAY_FIELDENUMS_HXX
