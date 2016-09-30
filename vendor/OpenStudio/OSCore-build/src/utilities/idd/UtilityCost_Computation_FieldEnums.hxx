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

#ifndef UTILITIES_IDD_UTILITYCOST_COMPUTATION_FIELDENUMS_HXX
#define UTILITIES_IDD_UTILITYCOST_COMPUTATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class UtilityCost_ComputationFields
 *  \brief Enumeration of UtilityCost:Computation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(UtilityCost_ComputationFields, )
#else
class UtilityCost_ComputationFields: public ::EnumBase<UtilityCost_ComputationFields> {
 public: 
  enum domain 
  {
Name, TariffName,   };
  UtilityCost_ComputationFields()
   : EnumBase<UtilityCost_ComputationFields>(Name) {} 
  UtilityCost_ComputationFields(const std::string &t_name) 
   : EnumBase<UtilityCost_ComputationFields>(t_name) {} 
  UtilityCost_ComputationFields(int t_value) 
   : EnumBase<UtilityCost_ComputationFields>(t_value) {} 
  static std::string enumName() 
  { return "UtilityCost_ComputationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<UtilityCost_ComputationFields>::value()); }
   private:
    friend class EnumBase<UtilityCost_ComputationFields>;
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
{ UtilityCost_ComputationFields::Name, "Name", "Name"},
{ UtilityCost_ComputationFields::TariffName, "TariffName", "Tariff Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const UtilityCost_ComputationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<UtilityCost_ComputationFields> OptionalUtilityCost_ComputationFields ;
#endif

/** \class UtilityCost_ComputationExtensibleFields
 *  \brief Enumeration of UtilityCost:Computation's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(UtilityCost_ComputationExtensibleFields, )
#else
class UtilityCost_ComputationExtensibleFields: public ::EnumBase<UtilityCost_ComputationExtensibleFields> {
 public: 
  enum domain 
  {
ComputeStep,   };
  UtilityCost_ComputationExtensibleFields()
   : EnumBase<UtilityCost_ComputationExtensibleFields>(ComputeStep) {} 
  UtilityCost_ComputationExtensibleFields(const std::string &t_name) 
   : EnumBase<UtilityCost_ComputationExtensibleFields>(t_name) {} 
  UtilityCost_ComputationExtensibleFields(int t_value) 
   : EnumBase<UtilityCost_ComputationExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "UtilityCost_ComputationExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<UtilityCost_ComputationExtensibleFields>::value()); }
   private:
    friend class EnumBase<UtilityCost_ComputationExtensibleFields>;
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
{ UtilityCost_ComputationExtensibleFields::ComputeStep, "ComputeStep", "Compute Step"},
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
  inline std::ostream &operator<<(std::ostream &os, const UtilityCost_ComputationExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<UtilityCost_ComputationExtensibleFields> OptionalUtilityCost_ComputationExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_UTILITYCOST_COMPUTATION_FIELDENUMS_HXX
