/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKEXTERNALNODE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKEXTERNALNODE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkExternalNodeFields
 *  \brief Enumeration of OS:AirflowNetworkExternalNode's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkExternalNodeFields, )
#else
class OS_AirflowNetworkExternalNodeFields: public ::EnumBase<OS_AirflowNetworkExternalNodeFields> {
 public: 
  enum domain 
  {
Handle, Name, ExternalNodeHeight, WindPressureCoefficientCurveName, SymmetricWindPressureCoefficientCurve, WindAngleType,   };
  OS_AirflowNetworkExternalNodeFields()
   : EnumBase<OS_AirflowNetworkExternalNodeFields>(Handle) {} 
  OS_AirflowNetworkExternalNodeFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkExternalNodeFields>(t_name) {} 
  OS_AirflowNetworkExternalNodeFields(int t_value) 
   : EnumBase<OS_AirflowNetworkExternalNodeFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkExternalNodeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkExternalNodeFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkExternalNodeFields>;
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
{ OS_AirflowNetworkExternalNodeFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkExternalNodeFields::Name, "Name", "Name"},
{ OS_AirflowNetworkExternalNodeFields::ExternalNodeHeight, "ExternalNodeHeight", "External Node Height"},
{ OS_AirflowNetworkExternalNodeFields::WindPressureCoefficientCurveName, "WindPressureCoefficientCurveName", "Wind Pressure Coefficient Curve Name"},
{ OS_AirflowNetworkExternalNodeFields::SymmetricWindPressureCoefficientCurve, "SymmetricWindPressureCoefficientCurve", "Symmetric Wind Pressure Coefficient Curve"},
{ OS_AirflowNetworkExternalNodeFields::WindAngleType, "WindAngleType", "Wind Angle Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkExternalNodeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkExternalNodeFields> OptionalOS_AirflowNetworkExternalNodeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKEXTERNALNODE_FIELDENUMS_HXX
