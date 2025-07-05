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

#ifndef UTILITIES_IDD_SOLARCOLLECTORPERFORMANCE_INTEGRALCOLLECTORSTORAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_SOLARCOLLECTORPERFORMANCE_INTEGRALCOLLECTORSTORAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SolarCollectorPerformance_IntegralCollectorStorageFields
 *  \brief Enumeration of SolarCollectorPerformance:IntegralCollectorStorage's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SolarCollectorPerformance_IntegralCollectorStorageFields, )
#else
class SolarCollectorPerformance_IntegralCollectorStorageFields: public ::EnumBase<SolarCollectorPerformance_IntegralCollectorStorageFields> {
 public: 
  enum domain 
  {
Name, ICSCollectorType, GrossArea, CollectorWaterVolume, BottomHeatLossConductance, SideHeatLossConductance, AspectRatio, CollectorSideHeight, ThermalMassofAbsorberPlate, NumberofCovers, CoverSpacing, RefractiveIndexofOuterCover, ExtinctionCoefficientTimesThicknessofOuterCover, EmissivityofOuterCover, RefractiveIndexofInnerCover, ExtinctionCoefficientTimesThicknessoftheinnerCover, EmissivityofInnerCover, AbsorptanceofAbsorberPlate, EmissivityofAbsorberPlate,   };
  SolarCollectorPerformance_IntegralCollectorStorageFields()
   : EnumBase<SolarCollectorPerformance_IntegralCollectorStorageFields>(Name) {} 
  SolarCollectorPerformance_IntegralCollectorStorageFields(const std::string &t_name) 
   : EnumBase<SolarCollectorPerformance_IntegralCollectorStorageFields>(t_name) {} 
  SolarCollectorPerformance_IntegralCollectorStorageFields(int t_value) 
   : EnumBase<SolarCollectorPerformance_IntegralCollectorStorageFields>(t_value) {} 
  static std::string enumName() 
  { return "SolarCollectorPerformance_IntegralCollectorStorageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SolarCollectorPerformance_IntegralCollectorStorageFields>::value()); }
   private:
    friend class EnumBase<SolarCollectorPerformance_IntegralCollectorStorageFields>;
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
{ SolarCollectorPerformance_IntegralCollectorStorageFields::Name, "Name", "Name"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::ICSCollectorType, "ICSCollectorType", "ICS Collector Type"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::GrossArea, "GrossArea", "Gross Area"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::CollectorWaterVolume, "CollectorWaterVolume", "Collector Water Volume"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::BottomHeatLossConductance, "BottomHeatLossConductance", "Bottom Heat Loss Conductance"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::SideHeatLossConductance, "SideHeatLossConductance", "Side Heat Loss Conductance"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::AspectRatio, "AspectRatio", "Aspect Ratio"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::CollectorSideHeight, "CollectorSideHeight", "Collector Side Height"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::ThermalMassofAbsorberPlate, "ThermalMassofAbsorberPlate", "Thermal Mass of Absorber Plate"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::NumberofCovers, "NumberofCovers", "Number of Covers"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::CoverSpacing, "CoverSpacing", "Cover Spacing"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::RefractiveIndexofOuterCover, "RefractiveIndexofOuterCover", "Refractive Index of Outer Cover"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::ExtinctionCoefficientTimesThicknessofOuterCover, "ExtinctionCoefficientTimesThicknessofOuterCover", "Extinction Coefficient Times Thickness of Outer Cover"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofOuterCover, "EmissivityofOuterCover", "Emissivity of Outer Cover"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::RefractiveIndexofInnerCover, "RefractiveIndexofInnerCover", "Refractive Index of Inner Cover"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::ExtinctionCoefficientTimesThicknessoftheinnerCover, "ExtinctionCoefficientTimesThicknessoftheinnerCover", "Extinction Coefficient Times Thickness of the inner Cover"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofInnerCover, "EmissivityofInnerCover", "Emissivity of Inner Cover"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::AbsorptanceofAbsorberPlate, "AbsorptanceofAbsorberPlate", "Absorptance of Absorber Plate"},
{ SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofAbsorberPlate, "EmissivityofAbsorberPlate", "Emissivity of Absorber Plate"},
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
  inline std::ostream &operator<<(std::ostream &os, const SolarCollectorPerformance_IntegralCollectorStorageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SolarCollectorPerformance_IntegralCollectorStorageFields> OptionalSolarCollectorPerformance_IntegralCollectorStorageFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SOLARCOLLECTORPERFORMANCE_INTEGRALCOLLECTORSTORAGE_FIELDENUMS_HXX
