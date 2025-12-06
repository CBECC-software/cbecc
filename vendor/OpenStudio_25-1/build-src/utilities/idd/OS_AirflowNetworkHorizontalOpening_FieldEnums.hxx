/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKHORIZONTALOPENING_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKHORIZONTALOPENING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkHorizontalOpeningFields
 *  \brief Enumeration of OS:AirflowNetworkHorizontalOpening's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkHorizontalOpeningFields, )
#else
class OS_AirflowNetworkHorizontalOpeningFields: public ::EnumBase<OS_AirflowNetworkHorizontalOpeningFields> {
 public: 
  enum domain 
  {
Handle, Name, AirMassFlowCoefficientWhenOpeningisClosed, AirMassFlowExponentWhenOpeningisClosed, SlopingPlaneAngle, DischargeCoefficient,   };
  OS_AirflowNetworkHorizontalOpeningFields()
   : EnumBase<OS_AirflowNetworkHorizontalOpeningFields>(Handle) {} 
  OS_AirflowNetworkHorizontalOpeningFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkHorizontalOpeningFields>(t_name) {} 
  OS_AirflowNetworkHorizontalOpeningFields(int t_value) 
   : EnumBase<OS_AirflowNetworkHorizontalOpeningFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkHorizontalOpeningFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkHorizontalOpeningFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkHorizontalOpeningFields>;
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
{ OS_AirflowNetworkHorizontalOpeningFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkHorizontalOpeningFields::Name, "Name", "Name"},
{ OS_AirflowNetworkHorizontalOpeningFields::AirMassFlowCoefficientWhenOpeningisClosed, "AirMassFlowCoefficientWhenOpeningisClosed", "Air Mass Flow Coefficient When Opening is Closed"},
{ OS_AirflowNetworkHorizontalOpeningFields::AirMassFlowExponentWhenOpeningisClosed, "AirMassFlowExponentWhenOpeningisClosed", "Air Mass Flow Exponent When Opening is Closed"},
{ OS_AirflowNetworkHorizontalOpeningFields::SlopingPlaneAngle, "SlopingPlaneAngle", "Sloping Plane Angle"},
{ OS_AirflowNetworkHorizontalOpeningFields::DischargeCoefficient, "DischargeCoefficient", "Discharge Coefficient"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkHorizontalOpeningFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkHorizontalOpeningFields> OptionalOS_AirflowNetworkHorizontalOpeningFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKHORIZONTALOPENING_FIELDENUMS_HXX
