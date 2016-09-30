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

#ifndef UTILITIES_IDD_OS_UTILITYCOST_COMPUTATION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_UTILITYCOST_COMPUTATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_UtilityCost_ComputationFields
 *  \brief Enumeration of OS:UtilityCost:Computation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_UtilityCost_ComputationFields, )
#else
class OS_UtilityCost_ComputationFields: public ::EnumBase<OS_UtilityCost_ComputationFields> {
 public: 
  enum domain 
  {
Handle, Name, TariffName,   };
  OS_UtilityCost_ComputationFields()
   : EnumBase<OS_UtilityCost_ComputationFields>(Handle) {} 
  OS_UtilityCost_ComputationFields(const std::string &t_name) 
   : EnumBase<OS_UtilityCost_ComputationFields>(t_name) {} 
  OS_UtilityCost_ComputationFields(int t_value) 
   : EnumBase<OS_UtilityCost_ComputationFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_UtilityCost_ComputationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_UtilityCost_ComputationFields>::value()); }
   private:
    friend class EnumBase<OS_UtilityCost_ComputationFields>;
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
{ OS_UtilityCost_ComputationFields::Handle, "Handle", "Handle"},
{ OS_UtilityCost_ComputationFields::Name, "Name", "Name"},
{ OS_UtilityCost_ComputationFields::TariffName, "TariffName", "Tariff Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_UtilityCost_ComputationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_UtilityCost_ComputationFields> OptionalOS_UtilityCost_ComputationFields ;
#endif

/** \class OS_UtilityCost_ComputationExtensibleFields
 *  \brief Enumeration of OS:UtilityCost:Computation's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_UtilityCost_ComputationExtensibleFields, )
#else
class OS_UtilityCost_ComputationExtensibleFields: public ::EnumBase<OS_UtilityCost_ComputationExtensibleFields> {
 public: 
  enum domain 
  {
ComputeStep,   };
  OS_UtilityCost_ComputationExtensibleFields()
   : EnumBase<OS_UtilityCost_ComputationExtensibleFields>(ComputeStep) {} 
  OS_UtilityCost_ComputationExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_UtilityCost_ComputationExtensibleFields>(t_name) {} 
  OS_UtilityCost_ComputationExtensibleFields(int t_value) 
   : EnumBase<OS_UtilityCost_ComputationExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_UtilityCost_ComputationExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_UtilityCost_ComputationExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_UtilityCost_ComputationExtensibleFields>;
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
{ OS_UtilityCost_ComputationExtensibleFields::ComputeStep, "ComputeStep", "Compute Step"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_UtilityCost_ComputationExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_UtilityCost_ComputationExtensibleFields> OptionalOS_UtilityCost_ComputationExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_UTILITYCOST_COMPUTATION_FIELDENUMS_HXX
