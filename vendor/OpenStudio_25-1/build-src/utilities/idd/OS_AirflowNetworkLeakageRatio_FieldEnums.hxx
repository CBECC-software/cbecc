/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKLEAKAGERATIO_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKLEAKAGERATIO_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkLeakageRatioFields
 *  \brief Enumeration of OS:AirflowNetworkLeakageRatio's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkLeakageRatioFields, )
#else
class OS_AirflowNetworkLeakageRatioFields: public ::EnumBase<OS_AirflowNetworkLeakageRatioFields> {
 public: 
  enum domain 
  {
Handle, Name, EffectiveLeakageRatio, MaximumFlowRate, ReferencePressureDifference, AirMassFlowExponent,   };
  OS_AirflowNetworkLeakageRatioFields()
   : EnumBase<OS_AirflowNetworkLeakageRatioFields>(Handle) {} 
  OS_AirflowNetworkLeakageRatioFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkLeakageRatioFields>(t_name) {} 
  OS_AirflowNetworkLeakageRatioFields(int t_value) 
   : EnumBase<OS_AirflowNetworkLeakageRatioFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkLeakageRatioFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkLeakageRatioFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkLeakageRatioFields>;
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
{ OS_AirflowNetworkLeakageRatioFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkLeakageRatioFields::Name, "Name", "Name"},
{ OS_AirflowNetworkLeakageRatioFields::EffectiveLeakageRatio, "EffectiveLeakageRatio", "Effective Leakage Ratio"},
{ OS_AirflowNetworkLeakageRatioFields::MaximumFlowRate, "MaximumFlowRate", "Maximum Flow Rate"},
{ OS_AirflowNetworkLeakageRatioFields::ReferencePressureDifference, "ReferencePressureDifference", "Reference Pressure Difference"},
{ OS_AirflowNetworkLeakageRatioFields::AirMassFlowExponent, "AirMassFlowExponent", "Air Mass Flow Exponent"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkLeakageRatioFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkLeakageRatioFields> OptionalOS_AirflowNetworkLeakageRatioFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKLEAKAGERATIO_FIELDENUMS_HXX
