/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_ZONEHVAC_BASEBOARD_RADIANTCONVECTIVE_STEAM_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_BASEBOARD_RADIANTCONVECTIVE_STEAM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_Baseboard_RadiantConvective_SteamFields
 *  \brief Enumeration of ZoneHVAC:Baseboard:RadiantConvective:Steam's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_Baseboard_RadiantConvective_SteamFields, )
#else
class ZoneHVAC_Baseboard_RadiantConvective_SteamFields: public ::EnumBase<ZoneHVAC_Baseboard_RadiantConvective_SteamFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, InletNodeName, OutletNodeName, HeatingDesignCapacityMethod, HeatingDesignCapacity, HeatingDesignCapacityPerFloorArea, FractionofAutosizedHeatingDesignCapacity, DegreeofSubCooling, MaximumSteamFlowRate, ConvergenceTolerance, FractionRadiant, FractionofRadiantEnergyIncidentonPeople,   };
  ZoneHVAC_Baseboard_RadiantConvective_SteamFields()
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_SteamFields>(Name) {} 
  ZoneHVAC_Baseboard_RadiantConvective_SteamFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_SteamFields>(t_name) {} 
  ZoneHVAC_Baseboard_RadiantConvective_SteamFields(int t_value) 
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_SteamFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_Baseboard_RadiantConvective_SteamFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_Baseboard_RadiantConvective_SteamFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_Baseboard_RadiantConvective_SteamFields>;
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
{ ZoneHVAC_Baseboard_RadiantConvective_SteamFields::Name, "Name", "Name"},
{ ZoneHVAC_Baseboard_RadiantConvective_SteamFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_Baseboard_RadiantConvective_SteamFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ ZoneHVAC_Baseboard_RadiantConvective_SteamFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ ZoneHVAC_Baseboard_RadiantConvective_SteamFields::HeatingDesignCapacityMethod, "HeatingDesignCapacityMethod", "Heating Design Capacity Method"},
{ ZoneHVAC_Baseboard_RadiantConvective_SteamFields::HeatingDesignCapacity, "HeatingDesignCapacity", "Heating Design Capacity"},
{ ZoneHVAC_Baseboard_RadiantConvective_SteamFields::HeatingDesignCapacityPerFloorArea, "HeatingDesignCapacityPerFloorArea", "Heating Design Capacity Per Floor Area"},
{ ZoneHVAC_Baseboard_RadiantConvective_SteamFields::FractionofAutosizedHeatingDesignCapacity, "FractionofAutosizedHeatingDesignCapacity", "Fraction of Autosized Heating Design Capacity"},
{ ZoneHVAC_Baseboard_RadiantConvective_SteamFields::DegreeofSubCooling, "DegreeofSubCooling", "Degree of SubCooling"},
{ ZoneHVAC_Baseboard_RadiantConvective_SteamFields::MaximumSteamFlowRate, "MaximumSteamFlowRate", "Maximum Steam Flow Rate"},
{ ZoneHVAC_Baseboard_RadiantConvective_SteamFields::ConvergenceTolerance, "ConvergenceTolerance", "Convergence Tolerance"},
{ ZoneHVAC_Baseboard_RadiantConvective_SteamFields::FractionRadiant, "FractionRadiant", "Fraction Radiant"},
{ ZoneHVAC_Baseboard_RadiantConvective_SteamFields::FractionofRadiantEnergyIncidentonPeople, "FractionofRadiantEnergyIncidentonPeople", "Fraction of Radiant Energy Incident on People"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_Baseboard_RadiantConvective_SteamFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_Baseboard_RadiantConvective_SteamFields> OptionalZoneHVAC_Baseboard_RadiantConvective_SteamFields ;
#endif

/** \class ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields
 *  \brief Enumeration of ZoneHVAC:Baseboard:RadiantConvective:Steam's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields, )
#else
class ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields: public ::EnumBase<ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceName, FractionofRadiantEnergytoSurface,   };
  ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields()
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields>(SurfaceName) {} 
  ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields>(t_name) {} 
  ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields(int t_value) 
   : EnumBase<ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields>;
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
{ ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
{ ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields::FractionofRadiantEnergytoSurface, "FractionofRadiantEnergytoSurface", "Fraction of Radiant Energy to Surface"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields> OptionalZoneHVAC_Baseboard_RadiantConvective_SteamExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_BASEBOARD_RADIANTCONVECTIVE_STEAM_FIELDENUMS_HXX
