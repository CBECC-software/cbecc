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

#ifndef UTILITIES_IDD_SITE_GROUNDTEMPERATURE_UNDISTURBED_XING_FIELDENUMS_HXX
#define UTILITIES_IDD_SITE_GROUNDTEMPERATURE_UNDISTURBED_XING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Site_GroundTemperature_Undisturbed_XingFields
 *  \brief Enumeration of Site:GroundTemperature:Undisturbed:Xing's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Site_GroundTemperature_Undisturbed_XingFields, )
#else
class Site_GroundTemperature_Undisturbed_XingFields: public ::EnumBase<Site_GroundTemperature_Undisturbed_XingFields> {
 public: 
  enum domain 
  {
Name, SoilThermalConductivity, SoilDensity, SoilSpecificHeat, AverageSoilSurfaceTempeature, SoilSurfaceTemperatureAmplitude1, SoilSurfaceTemperatureAmplitude2, PhaseShiftofTemperatureAmplitude1, PhaseShiftofTemperatureAmplitude2,   };
  Site_GroundTemperature_Undisturbed_XingFields()
   : EnumBase<Site_GroundTemperature_Undisturbed_XingFields>(Name) {} 
  Site_GroundTemperature_Undisturbed_XingFields(const std::string &t_name) 
   : EnumBase<Site_GroundTemperature_Undisturbed_XingFields>(t_name) {} 
  Site_GroundTemperature_Undisturbed_XingFields(int t_value) 
   : EnumBase<Site_GroundTemperature_Undisturbed_XingFields>(t_value) {} 
  static std::string enumName() 
  { return "Site_GroundTemperature_Undisturbed_XingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Site_GroundTemperature_Undisturbed_XingFields>::value()); }
   private:
    friend class EnumBase<Site_GroundTemperature_Undisturbed_XingFields>;
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
{ Site_GroundTemperature_Undisturbed_XingFields::Name, "Name", "Name"},
{ Site_GroundTemperature_Undisturbed_XingFields::SoilThermalConductivity, "SoilThermalConductivity", "Soil Thermal Conductivity"},
{ Site_GroundTemperature_Undisturbed_XingFields::SoilDensity, "SoilDensity", "Soil Density"},
{ Site_GroundTemperature_Undisturbed_XingFields::SoilSpecificHeat, "SoilSpecificHeat", "Soil Specific Heat"},
{ Site_GroundTemperature_Undisturbed_XingFields::AverageSoilSurfaceTempeature, "AverageSoilSurfaceTempeature", "Average Soil Surface Tempeature"},
{ Site_GroundTemperature_Undisturbed_XingFields::SoilSurfaceTemperatureAmplitude1, "SoilSurfaceTemperatureAmplitude1", "Soil Surface Temperature Amplitude 1"},
{ Site_GroundTemperature_Undisturbed_XingFields::SoilSurfaceTemperatureAmplitude2, "SoilSurfaceTemperatureAmplitude2", "Soil Surface Temperature Amplitude 2"},
{ Site_GroundTemperature_Undisturbed_XingFields::PhaseShiftofTemperatureAmplitude1, "PhaseShiftofTemperatureAmplitude1", "Phase Shift of Temperature Amplitude 1"},
{ Site_GroundTemperature_Undisturbed_XingFields::PhaseShiftofTemperatureAmplitude2, "PhaseShiftofTemperatureAmplitude2", "Phase Shift of Temperature Amplitude 2"},
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
  inline std::ostream &operator<<(std::ostream &os, const Site_GroundTemperature_Undisturbed_XingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Site_GroundTemperature_Undisturbed_XingFields> OptionalSite_GroundTemperature_Undisturbed_XingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SITE_GROUNDTEMPERATURE_UNDISTURBED_XING_FIELDENUMS_HXX
