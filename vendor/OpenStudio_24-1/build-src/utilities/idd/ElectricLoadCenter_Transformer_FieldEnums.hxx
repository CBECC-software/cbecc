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

#ifndef UTILITIES_IDD_ELECTRICLOADCENTER_TRANSFORMER_FIELDENUMS_HXX
#define UTILITIES_IDD_ELECTRICLOADCENTER_TRANSFORMER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ElectricLoadCenter_TransformerFields
 *  \brief Enumeration of ElectricLoadCenter:Transformer's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ElectricLoadCenter_TransformerFields, )
#else
class ElectricLoadCenter_TransformerFields: public ::EnumBase<ElectricLoadCenter_TransformerFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, TransformerUsage, ZoneName, RadiativeFraction, RatedCapacity, Phase, ConductorMaterial, FullLoadTemperatureRise, FractionofEddyCurrentLosses, PerformanceInputMethod, RatedNoLoadLoss, RatedLoadLoss, NameplateEfficiency, PerUnitLoadforNameplateEfficiency, ReferenceTemperatureforNameplateEfficiency, PerUnitLoadforMaximumEfficiency, ConsiderTransformerLossforUtilityCost,   };
  ElectricLoadCenter_TransformerFields()
   : EnumBase<ElectricLoadCenter_TransformerFields>(Name) {} 
  ElectricLoadCenter_TransformerFields(const std::string &t_name) 
   : EnumBase<ElectricLoadCenter_TransformerFields>(t_name) {} 
  ElectricLoadCenter_TransformerFields(int t_value) 
   : EnumBase<ElectricLoadCenter_TransformerFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricLoadCenter_TransformerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricLoadCenter_TransformerFields>::value()); }
   private:
    friend class EnumBase<ElectricLoadCenter_TransformerFields>;
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
{ ElectricLoadCenter_TransformerFields::Name, "Name", "Name"},
{ ElectricLoadCenter_TransformerFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ElectricLoadCenter_TransformerFields::TransformerUsage, "TransformerUsage", "Transformer Usage"},
{ ElectricLoadCenter_TransformerFields::ZoneName, "ZoneName", "Zone Name"},
{ ElectricLoadCenter_TransformerFields::RadiativeFraction, "RadiativeFraction", "Radiative Fraction"},
{ ElectricLoadCenter_TransformerFields::RatedCapacity, "RatedCapacity", "Rated Capacity"},
{ ElectricLoadCenter_TransformerFields::Phase, "Phase", "Phase"},
{ ElectricLoadCenter_TransformerFields::ConductorMaterial, "ConductorMaterial", "Conductor Material"},
{ ElectricLoadCenter_TransformerFields::FullLoadTemperatureRise, "FullLoadTemperatureRise", "Full Load Temperature Rise"},
{ ElectricLoadCenter_TransformerFields::FractionofEddyCurrentLosses, "FractionofEddyCurrentLosses", "Fraction of Eddy Current Losses"},
{ ElectricLoadCenter_TransformerFields::PerformanceInputMethod, "PerformanceInputMethod", "Performance Input Method"},
{ ElectricLoadCenter_TransformerFields::RatedNoLoadLoss, "RatedNoLoadLoss", "Rated No Load Loss"},
{ ElectricLoadCenter_TransformerFields::RatedLoadLoss, "RatedLoadLoss", "Rated Load Loss"},
{ ElectricLoadCenter_TransformerFields::NameplateEfficiency, "NameplateEfficiency", "Nameplate Efficiency"},
{ ElectricLoadCenter_TransformerFields::PerUnitLoadforNameplateEfficiency, "PerUnitLoadforNameplateEfficiency", "Per Unit Load for Nameplate Efficiency"},
{ ElectricLoadCenter_TransformerFields::ReferenceTemperatureforNameplateEfficiency, "ReferenceTemperatureforNameplateEfficiency", "Reference Temperature for Nameplate Efficiency"},
{ ElectricLoadCenter_TransformerFields::PerUnitLoadforMaximumEfficiency, "PerUnitLoadforMaximumEfficiency", "Per Unit Load for Maximum Efficiency"},
{ ElectricLoadCenter_TransformerFields::ConsiderTransformerLossforUtilityCost, "ConsiderTransformerLossforUtilityCost", "Consider Transformer Loss for Utility Cost"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricLoadCenter_TransformerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricLoadCenter_TransformerFields> OptionalElectricLoadCenter_TransformerFields ;
#endif

/** \class ElectricLoadCenter_TransformerExtensibleFields
 *  \brief Enumeration of ElectricLoadCenter:Transformer's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ElectricLoadCenter_TransformerExtensibleFields, )
#else
class ElectricLoadCenter_TransformerExtensibleFields: public ::EnumBase<ElectricLoadCenter_TransformerExtensibleFields> {
 public: 
  enum domain 
  {
MeterName,   };
  ElectricLoadCenter_TransformerExtensibleFields()
   : EnumBase<ElectricLoadCenter_TransformerExtensibleFields>(MeterName) {} 
  ElectricLoadCenter_TransformerExtensibleFields(const std::string &t_name) 
   : EnumBase<ElectricLoadCenter_TransformerExtensibleFields>(t_name) {} 
  ElectricLoadCenter_TransformerExtensibleFields(int t_value) 
   : EnumBase<ElectricLoadCenter_TransformerExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ElectricLoadCenter_TransformerExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ElectricLoadCenter_TransformerExtensibleFields>::value()); }
   private:
    friend class EnumBase<ElectricLoadCenter_TransformerExtensibleFields>;
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
{ ElectricLoadCenter_TransformerExtensibleFields::MeterName, "MeterName", "Meter Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ElectricLoadCenter_TransformerExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ElectricLoadCenter_TransformerExtensibleFields> OptionalElectricLoadCenter_TransformerExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ELECTRICLOADCENTER_TRANSFORMER_FIELDENUMS_HXX
