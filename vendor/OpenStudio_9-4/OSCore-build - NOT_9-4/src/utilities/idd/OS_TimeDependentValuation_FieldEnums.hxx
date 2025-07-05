/**********************************************************************
*  Copyright (c) 2008-2014, Alliance for Sustainable Energy.
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

#ifndef UTILITIES_IDD_OS_TIMEDEPENDENTVALUATION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_TIMEDEPENDENTVALUATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_TimeDependentValuationFields
 *  \brief Enumeration of OS:TimeDependentValuation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_TimeDependentValuationFields, )
#else
class OS_TimeDependentValuationFields: public ::EnumBase<OS_TimeDependentValuationFields> {
 public: 
  enum domain 
  {
Handle, Name, Url, Checksum, ActiveBuildingSector,   };
  OS_TimeDependentValuationFields()
   : EnumBase<OS_TimeDependentValuationFields>(Handle) {} 
  OS_TimeDependentValuationFields(const std::string &t_name) 
   : EnumBase<OS_TimeDependentValuationFields>(t_name) {} 
  OS_TimeDependentValuationFields(int t_value) 
   : EnumBase<OS_TimeDependentValuationFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_TimeDependentValuationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_TimeDependentValuationFields>::value()); }
   private:
    friend class EnumBase<OS_TimeDependentValuationFields>;
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
{ OS_TimeDependentValuationFields::Handle, "Handle", "Handle"},
{ OS_TimeDependentValuationFields::Name, "Name", "Name"},
{ OS_TimeDependentValuationFields::Url, "Url", "Url"},
{ OS_TimeDependentValuationFields::Checksum, "Checksum", "Checksum"},
{ OS_TimeDependentValuationFields::ActiveBuildingSector, "ActiveBuildingSector", "Active Building Sector"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_TimeDependentValuationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_TimeDependentValuationFields> OptionalOS_TimeDependentValuationFields ;
#endif

/** \class OS_TimeDependentValuationExtensibleFields
 *  \brief Enumeration of OS:TimeDependentValuation's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_TimeDependentValuationExtensibleFields, )
#else
class OS_TimeDependentValuationExtensibleFields: public ::EnumBase<OS_TimeDependentValuationExtensibleFields> {
 public: 
  enum domain 
  {
AvailableFuelType, CommercialColumnIndexForFuelType, ResidentialColumnIndexForFuelType,   };
  OS_TimeDependentValuationExtensibleFields()
   : EnumBase<OS_TimeDependentValuationExtensibleFields>(AvailableFuelType) {} 
  OS_TimeDependentValuationExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_TimeDependentValuationExtensibleFields>(t_name) {} 
  OS_TimeDependentValuationExtensibleFields(int t_value) 
   : EnumBase<OS_TimeDependentValuationExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_TimeDependentValuationExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_TimeDependentValuationExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_TimeDependentValuationExtensibleFields>;
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
{ OS_TimeDependentValuationExtensibleFields::AvailableFuelType, "AvailableFuelType", "Available Fuel Type"},
{ OS_TimeDependentValuationExtensibleFields::CommercialColumnIndexForFuelType, "CommercialColumnIndexForFuelType", "Commercial Column Index For Fuel Type"},
{ OS_TimeDependentValuationExtensibleFields::ResidentialColumnIndexForFuelType, "ResidentialColumnIndexForFuelType", "Residential Column Index For Fuel Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_TimeDependentValuationExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_TimeDependentValuationExtensibleFields> OptionalOS_TimeDependentValuationExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_TIMEDEPENDENTVALUATION_FIELDENUMS_HXX
