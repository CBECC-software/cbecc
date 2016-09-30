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

#ifndef UTILITIES_IDD_SITE_GROUNDTEMPERATURE_UNDISTURBED_KUSUDAACHENBACH_FIELDENUMS_HXX
#define UTILITIES_IDD_SITE_GROUNDTEMPERATURE_UNDISTURBED_KUSUDAACHENBACH_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Site_GroundTemperature_Undisturbed_KusudaAchenbachFields
 *  \brief Enumeration of Site:GroundTemperature:Undisturbed:KusudaAchenbach's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Site_GroundTemperature_Undisturbed_KusudaAchenbachFields, )
#else
class Site_GroundTemperature_Undisturbed_KusudaAchenbachFields: public ::EnumBase<Site_GroundTemperature_Undisturbed_KusudaAchenbachFields> {
 public: 
  enum domain 
  {
Name, SoilThermalConductivity, SoilDensity, SoilSpecificHeat, AverageSoilSurfaceTemperature, AverageAmplitudeofSurfaceTemperature, PhaseShiftofMinimumSurfaceTemperature,   };
  Site_GroundTemperature_Undisturbed_KusudaAchenbachFields()
   : EnumBase<Site_GroundTemperature_Undisturbed_KusudaAchenbachFields>(Name) {} 
  Site_GroundTemperature_Undisturbed_KusudaAchenbachFields(const std::string &t_name) 
   : EnumBase<Site_GroundTemperature_Undisturbed_KusudaAchenbachFields>(t_name) {} 
  Site_GroundTemperature_Undisturbed_KusudaAchenbachFields(int t_value) 
   : EnumBase<Site_GroundTemperature_Undisturbed_KusudaAchenbachFields>(t_value) {} 
  static std::string enumName() 
  { return "Site_GroundTemperature_Undisturbed_KusudaAchenbachFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Site_GroundTemperature_Undisturbed_KusudaAchenbachFields>::value()); }
   private:
    friend class EnumBase<Site_GroundTemperature_Undisturbed_KusudaAchenbachFields>;
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
{ Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::Name, "Name", "Name"},
{ Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::SoilThermalConductivity, "SoilThermalConductivity", "Soil Thermal Conductivity"},
{ Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::SoilDensity, "SoilDensity", "Soil Density"},
{ Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::SoilSpecificHeat, "SoilSpecificHeat", "Soil Specific Heat"},
{ Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::AverageSoilSurfaceTemperature, "AverageSoilSurfaceTemperature", "Average Soil Surface Temperature"},
{ Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::AverageAmplitudeofSurfaceTemperature, "AverageAmplitudeofSurfaceTemperature", "Average Amplitude of Surface Temperature"},
{ Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::PhaseShiftofMinimumSurfaceTemperature, "PhaseShiftofMinimumSurfaceTemperature", "Phase Shift of Minimum Surface Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const Site_GroundTemperature_Undisturbed_KusudaAchenbachFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Site_GroundTemperature_Undisturbed_KusudaAchenbachFields> OptionalSite_GroundTemperature_Undisturbed_KusudaAchenbachFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SITE_GROUNDTEMPERATURE_UNDISTURBED_KUSUDAACHENBACH_FIELDENUMS_HXX
