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

#ifndef UTILITIES_IDD_PHOTOVOLTAICPERFORMANCE_EQUIVALENTONEDIODE_FIELDENUMS_HXX
#define UTILITIES_IDD_PHOTOVOLTAICPERFORMANCE_EQUIVALENTONEDIODE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class PhotovoltaicPerformance_EquivalentOneDiodeFields
 *  \brief Enumeration of PhotovoltaicPerformance:EquivalentOne-Diode's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(PhotovoltaicPerformance_EquivalentOneDiodeFields, )
#else
class PhotovoltaicPerformance_EquivalentOneDiodeFields: public ::EnumBase<PhotovoltaicPerformance_EquivalentOneDiodeFields> {
 public: 
  enum domain 
  {
Name, Celltype, NumberofCellsinSeries, ActiveArea, TransmittanceAbsorptanceProduct, SemiconductorBandgap, ShuntResistance, ShortCircuitCurrent, OpenCircuitVoltage, ReferenceTemperature, ReferenceInsolation, ModuleCurrentatMaximumPower, ModuleVoltageatMaximumPower, TemperatureCoefficientofShortCircuitCurrent, TemperatureCoefficientofOpenCircuitVoltage, NominalOperatingCellTemperatureTestAmbientTemperature, NominalOperatingCellTemperatureTestCellTemperature, NominalOperatingCellTemperatureTestInsolation, ModuleHeatLossCoefficient, TotalHeatCapacity,   };
  PhotovoltaicPerformance_EquivalentOneDiodeFields()
   : EnumBase<PhotovoltaicPerformance_EquivalentOneDiodeFields>(Name) {} 
  PhotovoltaicPerformance_EquivalentOneDiodeFields(const std::string &t_name) 
   : EnumBase<PhotovoltaicPerformance_EquivalentOneDiodeFields>(t_name) {} 
  PhotovoltaicPerformance_EquivalentOneDiodeFields(int t_value) 
   : EnumBase<PhotovoltaicPerformance_EquivalentOneDiodeFields>(t_value) {} 
  static std::string enumName() 
  { return "PhotovoltaicPerformance_EquivalentOneDiodeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<PhotovoltaicPerformance_EquivalentOneDiodeFields>::value()); }
   private:
    friend class EnumBase<PhotovoltaicPerformance_EquivalentOneDiodeFields>;
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
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::Name, "Name", "Name"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::Celltype, "Celltype", "Cell type"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::NumberofCellsinSeries, "NumberofCellsinSeries", "Number of Cells in Series"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::ActiveArea, "ActiveArea", "Active Area"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::TransmittanceAbsorptanceProduct, "TransmittanceAbsorptanceProduct", "Transmittance Absorptance Product"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::SemiconductorBandgap, "SemiconductorBandgap", "Semiconductor Bandgap"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::ShuntResistance, "ShuntResistance", "Shunt Resistance"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::ShortCircuitCurrent, "ShortCircuitCurrent", "Short Circuit Current"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::OpenCircuitVoltage, "OpenCircuitVoltage", "Open Circuit Voltage"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::ReferenceTemperature, "ReferenceTemperature", "Reference Temperature"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::ReferenceInsolation, "ReferenceInsolation", "Reference Insolation"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::ModuleCurrentatMaximumPower, "ModuleCurrentatMaximumPower", "Module Current at Maximum Power"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::ModuleVoltageatMaximumPower, "ModuleVoltageatMaximumPower", "Module Voltage at Maximum Power"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::TemperatureCoefficientofShortCircuitCurrent, "TemperatureCoefficientofShortCircuitCurrent", "Temperature Coefficient of Short Circuit Current"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::TemperatureCoefficientofOpenCircuitVoltage, "TemperatureCoefficientofOpenCircuitVoltage", "Temperature Coefficient of Open Circuit Voltage"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::NominalOperatingCellTemperatureTestAmbientTemperature, "NominalOperatingCellTemperatureTestAmbientTemperature", "Nominal Operating Cell Temperature Test Ambient Temperature"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::NominalOperatingCellTemperatureTestCellTemperature, "NominalOperatingCellTemperatureTestCellTemperature", "Nominal Operating Cell Temperature Test Cell Temperature"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::NominalOperatingCellTemperatureTestInsolation, "NominalOperatingCellTemperatureTestInsolation", "Nominal Operating Cell Temperature Test Insolation"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::ModuleHeatLossCoefficient, "ModuleHeatLossCoefficient", "Module Heat Loss Coefficient"},
{ PhotovoltaicPerformance_EquivalentOneDiodeFields::TotalHeatCapacity, "TotalHeatCapacity", "Total Heat Capacity"},
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
  inline std::ostream &operator<<(std::ostream &os, const PhotovoltaicPerformance_EquivalentOneDiodeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<PhotovoltaicPerformance_EquivalentOneDiodeFields> OptionalPhotovoltaicPerformance_EquivalentOneDiodeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PHOTOVOLTAICPERFORMANCE_EQUIVALENTONEDIODE_FIELDENUMS_HXX
