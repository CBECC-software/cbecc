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

#ifndef UTILITIES_IDD_OS_SOLARCOLLECTORPERFORMANCE_INTEGRALCOLLECTORSTORAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SOLARCOLLECTORPERFORMANCE_INTEGRALCOLLECTORSTORAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SolarCollectorPerformance_IntegralCollectorStorageFields
 *  \brief Enumeration of OS:SolarCollectorPerformance:IntegralCollectorStorage's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SolarCollectorPerformance_IntegralCollectorStorageFields, )
#else
class OS_SolarCollectorPerformance_IntegralCollectorStorageFields: public ::EnumBase<OS_SolarCollectorPerformance_IntegralCollectorStorageFields> {
 public: 
  enum domain 
  {
Handle, Name, ICSCollectorType, GrossArea, CollectorWaterVolume, BottomHeatLossConductance, SideHeatLossConductance, AspectRatio, CollectorSideHeight, ThermalMassofAbsorberPlate, NumberofCovers, CoverSpacing, RefractiveIndexofOuterCover, ExtinctionCoefficientTimesThicknessofOuterCover, EmissivityofOuterCover, RefractiveIndexofInnerCover, ExtinctionCoefficientTimesThicknessoftheinnerCover, EmissivityofInnerCover, AbsorptanceofAbsorberPlate, EmissivityofAbsorberPlate,   };
  OS_SolarCollectorPerformance_IntegralCollectorStorageFields()
   : EnumBase<OS_SolarCollectorPerformance_IntegralCollectorStorageFields>(Handle) {} 
  OS_SolarCollectorPerformance_IntegralCollectorStorageFields(const std::string &t_name) 
   : EnumBase<OS_SolarCollectorPerformance_IntegralCollectorStorageFields>(t_name) {} 
  OS_SolarCollectorPerformance_IntegralCollectorStorageFields(int t_value) 
   : EnumBase<OS_SolarCollectorPerformance_IntegralCollectorStorageFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SolarCollectorPerformance_IntegralCollectorStorageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SolarCollectorPerformance_IntegralCollectorStorageFields>::value()); }
   private:
    friend class EnumBase<OS_SolarCollectorPerformance_IntegralCollectorStorageFields>;
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
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::Handle, "Handle", "Handle"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::Name, "Name", "Name"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::ICSCollectorType, "ICSCollectorType", "ICS Collector Type"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::GrossArea, "GrossArea", "Gross Area"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::CollectorWaterVolume, "CollectorWaterVolume", "Collector Water Volume"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::BottomHeatLossConductance, "BottomHeatLossConductance", "Bottom Heat Loss Conductance"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::SideHeatLossConductance, "SideHeatLossConductance", "Side Heat Loss Conductance"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::AspectRatio, "AspectRatio", "Aspect Ratio"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::CollectorSideHeight, "CollectorSideHeight", "Collector Side Height"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::ThermalMassofAbsorberPlate, "ThermalMassofAbsorberPlate", "Thermal Mass of Absorber Plate"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::NumberofCovers, "NumberofCovers", "Number of Covers"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::CoverSpacing, "CoverSpacing", "Cover Spacing"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::RefractiveIndexofOuterCover, "RefractiveIndexofOuterCover", "Refractive Index of Outer Cover"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::ExtinctionCoefficientTimesThicknessofOuterCover, "ExtinctionCoefficientTimesThicknessofOuterCover", "Extinction Coefficient Times Thickness of Outer Cover"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofOuterCover, "EmissivityofOuterCover", "Emissivity of Outer Cover"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::RefractiveIndexofInnerCover, "RefractiveIndexofInnerCover", "Refractive Index of Inner Cover"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::ExtinctionCoefficientTimesThicknessoftheinnerCover, "ExtinctionCoefficientTimesThicknessoftheinnerCover", "Extinction Coefficient Times Thickness of the inner Cover"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofInnerCover, "EmissivityofInnerCover", "Emissivity of Inner Cover"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::AbsorptanceofAbsorberPlate, "AbsorptanceofAbsorberPlate", "Absorptance of Absorber Plate"},
{ OS_SolarCollectorPerformance_IntegralCollectorStorageFields::EmissivityofAbsorberPlate, "EmissivityofAbsorberPlate", "Emissivity of Absorber Plate"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SolarCollectorPerformance_IntegralCollectorStorageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SolarCollectorPerformance_IntegralCollectorStorageFields> OptionalOS_SolarCollectorPerformance_IntegralCollectorStorageFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SOLARCOLLECTORPERFORMANCE_INTEGRALCOLLECTORSTORAGE_FIELDENUMS_HXX
