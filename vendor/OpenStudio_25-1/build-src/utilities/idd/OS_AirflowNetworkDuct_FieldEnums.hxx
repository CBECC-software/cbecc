/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKDUCT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKDUCT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkDuctFields
 *  \brief Enumeration of OS:AirflowNetworkDuct's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkDuctFields, )
#else
class OS_AirflowNetworkDuctFields: public ::EnumBase<OS_AirflowNetworkDuctFields> {
 public: 
  enum domain 
  {
Handle, Name, DuctLength, HydraulicDiameter, CrossSectionArea, SurfaceRoughness, CoefficientforLocalDynamicLossDuetoFitting, HeatTransmittanceCoefficient_UFactor_forDuctWallConstruction, OverallMoistureTransmittanceCoefficientfromAirtoAir, OutsideConvectionCoefficient, InsideConvectionCoefficient,   };
  OS_AirflowNetworkDuctFields()
   : EnumBase<OS_AirflowNetworkDuctFields>(Handle) {} 
  OS_AirflowNetworkDuctFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkDuctFields>(t_name) {} 
  OS_AirflowNetworkDuctFields(int t_value) 
   : EnumBase<OS_AirflowNetworkDuctFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkDuctFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkDuctFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkDuctFields>;
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
{ OS_AirflowNetworkDuctFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkDuctFields::Name, "Name", "Name"},
{ OS_AirflowNetworkDuctFields::DuctLength, "DuctLength", "Duct Length"},
{ OS_AirflowNetworkDuctFields::HydraulicDiameter, "HydraulicDiameter", "Hydraulic Diameter"},
{ OS_AirflowNetworkDuctFields::CrossSectionArea, "CrossSectionArea", "Cross Section Area"},
{ OS_AirflowNetworkDuctFields::SurfaceRoughness, "SurfaceRoughness", "Surface Roughness"},
{ OS_AirflowNetworkDuctFields::CoefficientforLocalDynamicLossDuetoFitting, "CoefficientforLocalDynamicLossDuetoFitting", "Coefficient for Local Dynamic Loss Due to Fitting"},
{ OS_AirflowNetworkDuctFields::HeatTransmittanceCoefficient_UFactor_forDuctWallConstruction, "HeatTransmittanceCoefficient_UFactor_forDuctWallConstruction", "Heat Transmittance Coefficient (U-Factor) for Duct Wall Construction"},
{ OS_AirflowNetworkDuctFields::OverallMoistureTransmittanceCoefficientfromAirtoAir, "OverallMoistureTransmittanceCoefficientfromAirtoAir", "Overall Moisture Transmittance Coefficient from Air to Air"},
{ OS_AirflowNetworkDuctFields::OutsideConvectionCoefficient, "OutsideConvectionCoefficient", "Outside Convection Coefficient"},
{ OS_AirflowNetworkDuctFields::InsideConvectionCoefficient, "InsideConvectionCoefficient", "Inside Convection Coefficient"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkDuctFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkDuctFields> OptionalOS_AirflowNetworkDuctFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKDUCT_FIELDENUMS_HXX
