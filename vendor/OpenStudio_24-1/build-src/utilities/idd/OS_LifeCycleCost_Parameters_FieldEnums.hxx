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
Handle, AnalysisType, DiscountingConvention, InflationApproach, RealDiscountRate, NominalDiscountRate, Inflation, BaseDateMonth, BaseDateYear, ServiceDateMonth, ServiceDateYear, LengthofStudyPeriodinYears, TaxRate, DepreciationMethod, UseNISTFuelEscalationRates, NISTRegion, NISTSector, ElectricityInflation, NaturalGasInflation, SteamInflation, GasolineInflation, DieselInflation, CoalInflation, FuelOil1Inflation, FuelOil2Inflation, PropaneInflation, WaterInflation, OtherFuel1Inflation, OtherFuel2Inflation,   };
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
{ OS_LifeCycleCost_ParametersFields::OtherFuel1Inflation, "OtherFuel1Inflation", "OtherFuel1 Inflation"},
{ OS_LifeCycleCost_ParametersFields::OtherFuel2Inflation, "OtherFuel2Inflation", "OtherFuel2 Inflation"},
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
