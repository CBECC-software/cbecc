/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKSIMPLEOPENING_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKSIMPLEOPENING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkSimpleOpeningFields
 *  \brief Enumeration of OS:AirflowNetworkSimpleOpening's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkSimpleOpeningFields, )
#else
class OS_AirflowNetworkSimpleOpeningFields: public ::EnumBase<OS_AirflowNetworkSimpleOpeningFields> {
 public: 
  enum domain 
  {
Handle, Name, AirMassFlowCoefficientWhenOpeningisClosed, AirMassFlowExponentWhenOpeningisClosed, MinimumDensityDifferenceforTwoWayFlow, DischargeCoefficient,   };
  OS_AirflowNetworkSimpleOpeningFields()
   : EnumBase<OS_AirflowNetworkSimpleOpeningFields>(Handle) {} 
  OS_AirflowNetworkSimpleOpeningFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkSimpleOpeningFields>(t_name) {} 
  OS_AirflowNetworkSimpleOpeningFields(int t_value) 
   : EnumBase<OS_AirflowNetworkSimpleOpeningFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkSimpleOpeningFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkSimpleOpeningFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkSimpleOpeningFields>;
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
{ OS_AirflowNetworkSimpleOpeningFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkSimpleOpeningFields::Name, "Name", "Name"},
{ OS_AirflowNetworkSimpleOpeningFields::AirMassFlowCoefficientWhenOpeningisClosed, "AirMassFlowCoefficientWhenOpeningisClosed", "Air Mass Flow Coefficient When Opening is Closed"},
{ OS_AirflowNetworkSimpleOpeningFields::AirMassFlowExponentWhenOpeningisClosed, "AirMassFlowExponentWhenOpeningisClosed", "Air Mass Flow Exponent When Opening is Closed"},
{ OS_AirflowNetworkSimpleOpeningFields::MinimumDensityDifferenceforTwoWayFlow, "MinimumDensityDifferenceforTwoWayFlow", "Minimum Density Difference for Two-Way Flow"},
{ OS_AirflowNetworkSimpleOpeningFields::DischargeCoefficient, "DischargeCoefficient", "Discharge Coefficient"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkSimpleOpeningFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkSimpleOpeningFields> OptionalOS_AirflowNetworkSimpleOpeningFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKSIMPLEOPENING_FIELDENUMS_HXX
