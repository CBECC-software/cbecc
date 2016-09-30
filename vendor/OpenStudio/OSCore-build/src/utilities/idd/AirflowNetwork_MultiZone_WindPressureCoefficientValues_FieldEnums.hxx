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

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_WINDPRESSURECOEFFICIENTVALUES_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_WINDPRESSURECOEFFICIENTVALUES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields
 *  \brief Enumeration of AirflowNetwork:MultiZone:WindPressureCoefficientValues's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields, )
#else
class AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields: public ::EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields> {
 public: 
  enum domain 
  {
Name, AirflowNetwork_MultiZone_WindPressureCoefficientArrayName,   };
  AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields()
   : EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields>(Name) {} 
  AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields>(t_name) {} 
  AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields(int t_value) 
   : EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields>::value()); }
   private:
    friend class EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields>;
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
{ AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields::Name, "Name", "Name"},
{ AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields::AirflowNetwork_MultiZone_WindPressureCoefficientArrayName, "AirflowNetwork_MultiZone_WindPressureCoefficientArrayName", "AirflowNetwork:MultiZone:WindPressureCoefficientArray Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_MultiZone_WindPressureCoefficientValuesFields> OptionalAirflowNetwork_MultiZone_WindPressureCoefficientValuesFields ;
#endif

/** \class AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields
 *  \brief Enumeration of AirflowNetwork:MultiZone:WindPressureCoefficientValues's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields, )
#else
class AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields: public ::EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields> {
 public: 
  enum domain 
  {
WindPressureCoefficientValue,   };
  AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields()
   : EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields>(WindPressureCoefficientValue) {} 
  AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields>(t_name) {} 
  AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields(int t_value) 
   : EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields>::value()); }
   private:
    friend class EnumBase<AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields>;
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
{ AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields::WindPressureCoefficientValue, "WindPressureCoefficientValue", "Wind Pressure Coefficient Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields> OptionalAirflowNetwork_MultiZone_WindPressureCoefficientValuesExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_WINDPRESSURECOEFFICIENTVALUES_FIELDENUMS_HXX
