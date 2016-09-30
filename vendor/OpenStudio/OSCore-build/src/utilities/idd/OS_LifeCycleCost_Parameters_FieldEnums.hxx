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

#ifndef UTILITIES_IDD_OS_LIFECYCLECOST_PARAMETERS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_LIFECYCLECOST_PARAMETERS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_LifeCycleCost_ParametersFields
 *  \brief Enumeration of OS:LifeCycleCost:Parameters's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_LifeCycleCost_ParametersFields, )
#else
class OS_LifeCycleCost_ParametersFields: public ::EnumBase<OS_LifeCycleCost_ParametersFields> {
 public: 
  enum domain 
  {
Handle, AnalysisType, DiscountingConvention, InflationApproach, RealDiscountRate, NominalDiscountRate, Inflation, BaseDateMonth, BaseDateYear, ServiceDateMonth, ServiceDateYear, LengthofStudyPeriodinYears, TaxRate, DepreciationMethod, UseNISTFuelEscalationRates, NISTRegion, NISTSector, ElectricityInflation, NaturalGasInflation, SteamInflation, GasolineInflation, DieselInflation, CoalInflation, FuelOil1Inflation, FuelOil2Inflation, PropaneInflation, WaterInflation,   };
  OS_LifeCycleCost_ParametersFields()
   : EnumBase<OS_LifeCycleCost_ParametersFields>(Handle) {} 
  OS_LifeCycleCost_ParametersFields(const std::string &t_name) 
   : EnumBase<OS_LifeCycleCost_ParametersFields>(t_name) {} 
  OS_LifeCycleCost_ParametersFields(int t_value) 
   : EnumBase<OS_LifeCycleCost_ParametersFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_LifeCycleCost_ParametersFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_LifeCycleCost_ParametersFields>::value()); }
   private:
    friend class EnumBase<OS_LifeCycleCost_ParametersFields>;
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
{ OS_LifeCycleCost_ParametersFields::Handle, "Handle", "Handle"},
{ OS_LifeCycleCost_ParametersFields::AnalysisType, "AnalysisType", "Analysis Type"},
{ OS_LifeCycleCost_ParametersFields::DiscountingConvention, "DiscountingConvention", "Discounting Convention"},
{ OS_LifeCycleCost_ParametersFields::InflationApproach, "InflationApproach", "Inflation Approach"},
{ OS_LifeCycleCost_ParametersFields::RealDiscountRate, "RealDiscountRate", "Real Discount Rate"},
{ OS_LifeCycleCost_ParametersFields::NominalDiscountRate, "NominalDiscountRate", "Nominal Discount Rate"},
{ OS_LifeCycleCost_ParametersFields::Inflation, "Inflation", "Inflation"},
{ OS_LifeCycleCost_ParametersFields::BaseDateMonth, "BaseDateMonth", "Base Date Month"},
{ OS_LifeCycleCost_ParametersFields::BaseDateYear, "BaseDateYear", "Base Date Year"},
{ OS_LifeCycleCost_ParametersFields::ServiceDateMonth, "ServiceDateMonth", "Service Date Month"},
{ OS_LifeCycleCost_ParametersFields::ServiceDateYear, "ServiceDateYear", "Service Date Year"},
{ OS_LifeCycleCost_ParametersFields::LengthofStudyPeriodinYears, "LengthofStudyPeriodinYears", "Length of Study Period in Years"},
{ OS_LifeCycleCost_ParametersFields::TaxRate, "TaxRate", "Tax Rate"},
{ OS_LifeCycleCost_ParametersFields::DepreciationMethod, "DepreciationMethod", "Depreciation Method"},
{ OS_LifeCycleCost_ParametersFields::UseNISTFuelEscalationRates, "UseNISTFuelEscalationRates", "Use NIST Fuel Escalation Rates"},
{ OS_LifeCycleCost_ParametersFields::NISTRegion, "NISTRegion", "NIST Region"},
{ OS_LifeCycleCost_ParametersFields::NISTSector, "NISTSector", "NIST Sector"},
{ OS_LifeCycleCost_ParametersFields::ElectricityInflation, "ElectricityInflation", "Electricity Inflation"},
{ OS_LifeCycleCost_ParametersFields::NaturalGasInflation, "NaturalGasInflation", "NaturalGas Inflation"},
{ OS_LifeCycleCost_ParametersFields::SteamInflation, "SteamInflation", "Steam Inflation"},
{ OS_LifeCycleCost_ParametersFields::GasolineInflation, "GasolineInflation", "Gasoline Inflation"},
{ OS_LifeCycleCost_ParametersFields::DieselInflation, "DieselInflation", "Diesel Inflation"},
{ OS_LifeCycleCost_ParametersFields::CoalInflation, "CoalInflation", "Coal Inflation"},
{ OS_LifeCycleCost_ParametersFields::FuelOil1Inflation, "FuelOil1Inflation", "FuelOil1 Inflation"},
{ OS_LifeCycleCost_ParametersFields::FuelOil2Inflation, "FuelOil2Inflation", "FuelOil2 Inflation"},
{ OS_LifeCycleCost_ParametersFields::PropaneInflation, "PropaneInflation", "Propane Inflation"},
{ OS_LifeCycleCost_ParametersFields::WaterInflation, "WaterInflation", "Water Inflation"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_LifeCycleCost_ParametersFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_LifeCycleCost_ParametersFields> OptionalOS_LifeCycleCost_ParametersFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_LIFECYCLECOST_PARAMETERS_FIELDENUMS_HXX
