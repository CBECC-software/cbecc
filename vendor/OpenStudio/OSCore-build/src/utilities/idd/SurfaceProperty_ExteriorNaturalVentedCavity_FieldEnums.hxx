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

#ifndef UTILITIES_IDD_SURFACEPROPERTY_EXTERIORNATURALVENTEDCAVITY_FIELDENUMS_HXX
#define UTILITIES_IDD_SURFACEPROPERTY_EXTERIORNATURALVENTEDCAVITY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SurfaceProperty_ExteriorNaturalVentedCavityFields
 *  \brief Enumeration of SurfaceProperty:ExteriorNaturalVentedCavity's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SurfaceProperty_ExteriorNaturalVentedCavityFields, )
#else
class SurfaceProperty_ExteriorNaturalVentedCavityFields: public ::EnumBase<SurfaceProperty_ExteriorNaturalVentedCavityFields> {
 public: 
  enum domain 
  {
Name, BoundaryConditionsModelName, AreaFractionofOpenings, ThermalEmissivityofExteriorBaffleMaterial, SolarAbsorbtivityofExteriorBaffle, HeightScaleforBuoyancyDrivenVentilation, EffectiveThicknessofCavityBehindExteriorBaffle, RatioofActualSurfaceAreatoProjectedSurfaceArea, RoughnessofExteriorSurface, EffectivenessforPerforationswithRespecttoWind, DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow,   };
  SurfaceProperty_ExteriorNaturalVentedCavityFields()
   : EnumBase<SurfaceProperty_ExteriorNaturalVentedCavityFields>(Name) {} 
  SurfaceProperty_ExteriorNaturalVentedCavityFields(const std::string &t_name) 
   : EnumBase<SurfaceProperty_ExteriorNaturalVentedCavityFields>(t_name) {} 
  SurfaceProperty_ExteriorNaturalVentedCavityFields(int t_value) 
   : EnumBase<SurfaceProperty_ExteriorNaturalVentedCavityFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceProperty_ExteriorNaturalVentedCavityFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceProperty_ExteriorNaturalVentedCavityFields>::value()); }
   private:
    friend class EnumBase<SurfaceProperty_ExteriorNaturalVentedCavityFields>;
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
{ SurfaceProperty_ExteriorNaturalVentedCavityFields::Name, "Name", "Name"},
{ SurfaceProperty_ExteriorNaturalVentedCavityFields::BoundaryConditionsModelName, "BoundaryConditionsModelName", "Boundary Conditions Model Name"},
{ SurfaceProperty_ExteriorNaturalVentedCavityFields::AreaFractionofOpenings, "AreaFractionofOpenings", "Area Fraction of Openings"},
{ SurfaceProperty_ExteriorNaturalVentedCavityFields::ThermalEmissivityofExteriorBaffleMaterial, "ThermalEmissivityofExteriorBaffleMaterial", "Thermal Emissivity of Exterior Baffle Material"},
{ SurfaceProperty_ExteriorNaturalVentedCavityFields::SolarAbsorbtivityofExteriorBaffle, "SolarAbsorbtivityofExteriorBaffle", "Solar Absorbtivity of Exterior Baffle"},
{ SurfaceProperty_ExteriorNaturalVentedCavityFields::HeightScaleforBuoyancyDrivenVentilation, "HeightScaleforBuoyancyDrivenVentilation", "Height Scale for Buoyancy-Driven Ventilation"},
{ SurfaceProperty_ExteriorNaturalVentedCavityFields::EffectiveThicknessofCavityBehindExteriorBaffle, "EffectiveThicknessofCavityBehindExteriorBaffle", "Effective Thickness of Cavity Behind Exterior Baffle"},
{ SurfaceProperty_ExteriorNaturalVentedCavityFields::RatioofActualSurfaceAreatoProjectedSurfaceArea, "RatioofActualSurfaceAreatoProjectedSurfaceArea", "Ratio of Actual Surface Area to Projected Surface Area"},
{ SurfaceProperty_ExteriorNaturalVentedCavityFields::RoughnessofExteriorSurface, "RoughnessofExteriorSurface", "Roughness of Exterior Surface"},
{ SurfaceProperty_ExteriorNaturalVentedCavityFields::EffectivenessforPerforationswithRespecttoWind, "EffectivenessforPerforationswithRespecttoWind", "Effectiveness for Perforations with Respect to Wind"},
{ SurfaceProperty_ExteriorNaturalVentedCavityFields::DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow, "DischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow", "Discharge Coefficient for Openings with Respect to Buoyancy Driven Flow"},
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
  inline std::ostream &operator<<(std::ostream &os, const SurfaceProperty_ExteriorNaturalVentedCavityFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceProperty_ExteriorNaturalVentedCavityFields> OptionalSurfaceProperty_ExteriorNaturalVentedCavityFields ;
#endif

/** \class SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields
 *  \brief Enumeration of SurfaceProperty:ExteriorNaturalVentedCavity's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields, )
#else
class SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields: public ::EnumBase<SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceName,   };
  SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields()
   : EnumBase<SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields>(SurfaceName) {} 
  SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields(const std::string &t_name) 
   : EnumBase<SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields>(t_name) {} 
  SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields(int t_value) 
   : EnumBase<SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields>::value()); }
   private:
    friend class EnumBase<SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields>;
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
{ SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields> OptionalSurfaceProperty_ExteriorNaturalVentedCavityExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SURFACEPROPERTY_EXTERIORNATURALVENTEDCAVITY_FIELDENUMS_HXX
