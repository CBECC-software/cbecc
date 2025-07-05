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

#ifndef UTILITIES_IDD_PLANTEQUIPMENTOPERATION_HEATINGLOAD_FIELDENUMS_HXX
#define UTILITIES_IDD_PLANTEQUIPMENTOPERATION_HEATINGLOAD_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PlantEquipmentOperation_HeatingLoadFields
 *  \brief Enumeration of PlantEquipmentOperation:HeatingLoad's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PlantEquipmentOperation_HeatingLoadFields, )
#else
class PlantEquipmentOperation_HeatingLoadFields: public ::EnumBase<PlantEquipmentOperation_HeatingLoadFields> {
 public: 
  enum domain 
  {
Name,   };
  PlantEquipmentOperation_HeatingLoadFields()
   : EnumBase<PlantEquipmentOperation_HeatingLoadFields>(Name) {} 
  PlantEquipmentOperation_HeatingLoadFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_HeatingLoadFields>(t_name) {} 
  PlantEquipmentOperation_HeatingLoadFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_HeatingLoadFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_HeatingLoadFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_HeatingLoadFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_HeatingLoadFields>;
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
{ PlantEquipmentOperation_HeatingLoadFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_HeatingLoadFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_HeatingLoadFields> OptionalPlantEquipmentOperation_HeatingLoadFields ;
#endif

/** \class PlantEquipmentOperation_HeatingLoadExtensibleFields
 *  \brief Enumeration of PlantEquipmentOperation:HeatingLoad's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(PlantEquipmentOperation_HeatingLoadExtensibleFields, )
#else
class PlantEquipmentOperation_HeatingLoadExtensibleFields: public ::EnumBase<PlantEquipmentOperation_HeatingLoadExtensibleFields> {
 public: 
  enum domain 
  {
LoadRangeLowerLimit, LoadRangeUpperLimit, RangeEquipmentListName,   };
  PlantEquipmentOperation_HeatingLoadExtensibleFields()
   : EnumBase<PlantEquipmentOperation_HeatingLoadExtensibleFields>(LoadRangeLowerLimit) {} 
  PlantEquipmentOperation_HeatingLoadExtensibleFields(const std::string &t_name) 
   : EnumBase<PlantEquipmentOperation_HeatingLoadExtensibleFields>(t_name) {} 
  PlantEquipmentOperation_HeatingLoadExtensibleFields(int t_value) 
   : EnumBase<PlantEquipmentOperation_HeatingLoadExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "PlantEquipmentOperation_HeatingLoadExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PlantEquipmentOperation_HeatingLoadExtensibleFields>::value()); }
   private:
    friend class EnumBase<PlantEquipmentOperation_HeatingLoadExtensibleFields>;
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
{ PlantEquipmentOperation_HeatingLoadExtensibleFields::LoadRangeLowerLimit, "LoadRangeLowerLimit", "Load Range Lower Limit"},
{ PlantEquipmentOperation_HeatingLoadExtensibleFields::LoadRangeUpperLimit, "LoadRangeUpperLimit", "Load Range Upper Limit"},
{ PlantEquipmentOperation_HeatingLoadExtensibleFields::RangeEquipmentListName, "RangeEquipmentListName", "Range Equipment List Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const PlantEquipmentOperation_HeatingLoadExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PlantEquipmentOperation_HeatingLoadExtensibleFields> OptionalPlantEquipmentOperation_HeatingLoadExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PLANTEQUIPMENTOPERATION_HEATINGLOAD_FIELDENUMS_HXX
