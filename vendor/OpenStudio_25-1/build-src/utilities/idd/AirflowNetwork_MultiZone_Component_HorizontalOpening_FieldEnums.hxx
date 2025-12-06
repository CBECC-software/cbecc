/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_COMPONENT_HORIZONTALOPENING_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_COMPONENT_HORIZONTALOPENING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_MultiZone_Component_HorizontalOpeningFields
 *  \brief Enumeration of AirflowNetwork:MultiZone:Component:HorizontalOpening's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_MultiZone_Component_HorizontalOpeningFields, )
#else
class AirflowNetwork_MultiZone_Component_HorizontalOpeningFields: public ::EnumBase<AirflowNetwork_MultiZone_Component_HorizontalOpeningFields> {
 public: 
  enum domain 
  {
Name, AirMassFlowCoefficientWhenOpeningisClosed, AirMassFlowExponentWhenOpeningisClosed, SlopingPlaneAngle, DischargeCoefficient,   };
  AirflowNetwork_MultiZone_Component_HorizontalOpeningFields()
   : EnumBase<AirflowNetwork_MultiZone_Component_HorizontalOpeningFields>(Name) {} 
  AirflowNetwork_MultiZone_Component_HorizontalOpeningFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_MultiZone_Component_HorizontalOpeningFields>(t_name) {} 
  AirflowNetwork_MultiZone_Component_HorizontalOpeningFields(int t_value) 
   : EnumBase<AirflowNetwork_MultiZone_Component_HorizontalOpeningFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_MultiZone_Component_HorizontalOpeningFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_MultiZone_Component_HorizontalOpeningFields>::integer_value()); }
   private:
    friend class EnumBase<AirflowNetwork_MultiZone_Component_HorizontalOpeningFields>;
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
{ AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::Name, "Name", "Name"},
{ AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::AirMassFlowCoefficientWhenOpeningisClosed, "AirMassFlowCoefficientWhenOpeningisClosed", "Air Mass Flow Coefficient When Opening is Closed"},
{ AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::AirMassFlowExponentWhenOpeningisClosed, "AirMassFlowExponentWhenOpeningisClosed", "Air Mass Flow Exponent When Opening is Closed"},
{ AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::SlopingPlaneAngle, "SlopingPlaneAngle", "Sloping Plane Angle"},
{ AirflowNetwork_MultiZone_Component_HorizontalOpeningFields::DischargeCoefficient, "DischargeCoefficient", "Discharge Coefficient"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_MultiZone_Component_HorizontalOpeningFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_MultiZone_Component_HorizontalOpeningFields> OptionalAirflowNetwork_MultiZone_Component_HorizontalOpeningFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_COMPONENT_HORIZONTALOPENING_FIELDENUMS_HXX
