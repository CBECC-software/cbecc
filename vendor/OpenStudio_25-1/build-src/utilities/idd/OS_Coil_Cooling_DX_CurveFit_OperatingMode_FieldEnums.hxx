/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_COOLING_DX_CURVEFIT_OPERATINGMODE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_COOLING_DX_CURVEFIT_OPERATINGMODE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Cooling_DX_CurveFit_OperatingModeFields
 *  \brief Enumeration of OS:Coil:Cooling:DX:CurveFit:OperatingMode's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Cooling_DX_CurveFit_OperatingModeFields, )
#else
class OS_Coil_Cooling_DX_CurveFit_OperatingModeFields: public ::EnumBase<OS_Coil_Cooling_DX_CurveFit_OperatingModeFields> {
 public: 
  enum domain 
  {
Handle, Name, RatedGrossTotalCoolingCapacity, RatedEvaporatorAirFlowRate, RatedCondenserAirFlowRate, MaximumCyclingRate, RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, LatentCapacityTimeConstant, NominalTimeforCondensateRemovaltoBegin, ApplyLatentDegradationtoSpeedsGreaterthan1, CondenserType, NominalEvaporativeCondenserPumpPower, NominalSpeedNumber,   };
  OS_Coil_Cooling_DX_CurveFit_OperatingModeFields()
   : EnumBase<OS_Coil_Cooling_DX_CurveFit_OperatingModeFields>(Handle) {} 
  OS_Coil_Cooling_DX_CurveFit_OperatingModeFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_DX_CurveFit_OperatingModeFields>(t_name) {} 
  OS_Coil_Cooling_DX_CurveFit_OperatingModeFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_DX_CurveFit_OperatingModeFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_DX_CurveFit_OperatingModeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_DX_CurveFit_OperatingModeFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_DX_CurveFit_OperatingModeFields>;
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
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeFields::Handle, "Handle", "Handle"},
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeFields::Name, "Name", "Name"},
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedGrossTotalCoolingCapacity, "RatedGrossTotalCoolingCapacity", "Rated Gross Total Cooling Capacity"},
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedEvaporatorAirFlowRate, "RatedEvaporatorAirFlowRate", "Rated Evaporator Air Flow Rate"},
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedCondenserAirFlowRate, "RatedCondenserAirFlowRate", "Rated Condenser Air Flow Rate"},
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeFields::MaximumCyclingRate, "MaximumCyclingRate", "Maximum Cycling Rate"},
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, "RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity", "Ratio of Initial Moisture Evaporation Rate and Steady State Latent Capacity"},
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeFields::LatentCapacityTimeConstant, "LatentCapacityTimeConstant", "Latent Capacity Time Constant"},
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalTimeforCondensateRemovaltoBegin, "NominalTimeforCondensateRemovaltoBegin", "Nominal Time for Condensate Removal to Begin"},
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeFields::ApplyLatentDegradationtoSpeedsGreaterthan1, "ApplyLatentDegradationtoSpeedsGreaterthan1", "Apply Latent Degradation to Speeds Greater than 1"},
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeFields::CondenserType, "CondenserType", "Condenser Type"},
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalEvaporativeCondenserPumpPower, "NominalEvaporativeCondenserPumpPower", "Nominal Evaporative Condenser Pump Power"},
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalSpeedNumber, "NominalSpeedNumber", "Nominal Speed Number"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_DX_CurveFit_OperatingModeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_DX_CurveFit_OperatingModeFields> OptionalOS_Coil_Cooling_DX_CurveFit_OperatingModeFields ;
#endif

/** \class OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields
 *  \brief Enumeration of OS:Coil:Cooling:DX:CurveFit:OperatingMode's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields, )
#else
class OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields: public ::EnumBase<OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields> {
 public: 
  enum domain 
  {
Speed,   };
  OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields()
   : EnumBase<OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields>(Speed) {} 
  OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields>(t_name) {} 
  OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields>;
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
{ OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields::Speed, "Speed", "Speed"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields> OptionalOS_Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_COOLING_DX_CURVEFIT_OPERATINGMODE_FIELDENUMS_HXX
