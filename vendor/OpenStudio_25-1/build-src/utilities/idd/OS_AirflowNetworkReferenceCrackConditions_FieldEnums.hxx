/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKREFERENCECRACKCONDITIONS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKREFERENCECRACKCONDITIONS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkReferenceCrackConditionsFields
 *  \brief Enumeration of OS:AirflowNetworkReferenceCrackConditions's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkReferenceCrackConditionsFields, )
#else
class OS_AirflowNetworkReferenceCrackConditionsFields: public ::EnumBase<OS_AirflowNetworkReferenceCrackConditionsFields> {
 public: 
  enum domain 
  {
Handle, Name, ReferenceTemperature, ReferenceBarometricPressure, ReferenceHumidityRatio,   };
  OS_AirflowNetworkReferenceCrackConditionsFields()
   : EnumBase<OS_AirflowNetworkReferenceCrackConditionsFields>(Handle) {} 
  OS_AirflowNetworkReferenceCrackConditionsFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkReferenceCrackConditionsFields>(t_name) {} 
  OS_AirflowNetworkReferenceCrackConditionsFields(int t_value) 
   : EnumBase<OS_AirflowNetworkReferenceCrackConditionsFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkReferenceCrackConditionsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkReferenceCrackConditionsFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkReferenceCrackConditionsFields>;
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
{ OS_AirflowNetworkReferenceCrackConditionsFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkReferenceCrackConditionsFields::Name, "Name", "Name"},
{ OS_AirflowNetworkReferenceCrackConditionsFields::ReferenceTemperature, "ReferenceTemperature", "Reference Temperature"},
{ OS_AirflowNetworkReferenceCrackConditionsFields::ReferenceBarometricPressure, "ReferenceBarometricPressure", "Reference Barometric Pressure"},
{ OS_AirflowNetworkReferenceCrackConditionsFields::ReferenceHumidityRatio, "ReferenceHumidityRatio", "Reference Humidity Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkReferenceCrackConditionsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkReferenceCrackConditionsFields> OptionalOS_AirflowNetworkReferenceCrackConditionsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKREFERENCECRACKCONDITIONS_FIELDENUMS_HXX
