/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_PLANTEQUIPMENTOPERATION_OUTDOORDEWPOINTDIFFERENCE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PLANTEQUIPMENTOPERATION_OUTDOORDEWPOINTDIFFERENCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields
 *  \brief Enumeration of OS:PlantEquipmentOperation:OutdoorDewpointDifference's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields, )
#else
class OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields: public ::EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields> {
 public: 
  enum domain 
  {
Handle, Name, ReferenceTemperatureNodeName,   };
  OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields()
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields>(Handle) {} 
  OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields(const std::string &t_name) 
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields>(t_name) {} 
  OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields(int t_value) 
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields>::value()); }
   private:
    friend class EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields>;
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
{ OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields::Handle, "Handle", "Handle"},
{ OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields::Name, "Name", "Name"},
{ OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields::ReferenceTemperatureNodeName, "ReferenceTemperatureNodeName", "Reference Temperature Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields> OptionalOS_PlantEquipmentOperation_OutdoorDewpointDifferenceFields ;
#endif

/** \class OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields
 *  \brief Enumeration of OS:PlantEquipmentOperation:OutdoorDewpointDifference's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields, )
#else
class OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields: public ::EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields> {
 public: 
  enum domain 
  {
DryBulbTemperatureDifferenceRangeLowerLimit, DryBulbTemperatureDifferenceRangeUpperLimit, RangeEquipmentListName,   };
  OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields()
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields>(DryBulbTemperatureDifferenceRangeLowerLimit) {} 
  OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields>(t_name) {} 
  OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields(int t_value) 
   : EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields>;
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
{ OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields::DryBulbTemperatureDifferenceRangeLowerLimit, "DryBulbTemperatureDifferenceRangeLowerLimit", "Dry-Bulb Temperature Difference Range Lower Limit"},
{ OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields::DryBulbTemperatureDifferenceRangeUpperLimit, "DryBulbTemperatureDifferenceRangeUpperLimit", "Dry-Bulb Temperature Difference Range Upper Limit"},
{ OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields::RangeEquipmentListName, "RangeEquipmentListName", "Range Equipment List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields> OptionalOS_PlantEquipmentOperation_OutdoorDewpointDifferenceExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PLANTEQUIPMENTOPERATION_OUTDOORDEWPOINTDIFFERENCE_FIELDENUMS_HXX
