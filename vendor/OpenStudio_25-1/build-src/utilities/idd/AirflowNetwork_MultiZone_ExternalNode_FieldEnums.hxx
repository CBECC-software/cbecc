/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_EXTERNALNODE_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_EXTERNALNODE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_MultiZone_ExternalNodeFields
 *  \brief Enumeration of AirflowNetwork:MultiZone:ExternalNode's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_MultiZone_ExternalNodeFields, )
#else
class AirflowNetwork_MultiZone_ExternalNodeFields: public ::EnumBase<AirflowNetwork_MultiZone_ExternalNodeFields> {
 public: 
  enum domain 
  {
Name, ExternalNodeHeight, WindPressureCoefficientCurveName, SymmetricWindPressureCoefficientCurve, WindAngleType,   };
  AirflowNetwork_MultiZone_ExternalNodeFields()
   : EnumBase<AirflowNetwork_MultiZone_ExternalNodeFields>(Name) {} 
  AirflowNetwork_MultiZone_ExternalNodeFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_MultiZone_ExternalNodeFields>(t_name) {} 
  AirflowNetwork_MultiZone_ExternalNodeFields(int t_value) 
   : EnumBase<AirflowNetwork_MultiZone_ExternalNodeFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_MultiZone_ExternalNodeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_MultiZone_ExternalNodeFields>::integer_value()); }
   private:
    friend class EnumBase<AirflowNetwork_MultiZone_ExternalNodeFields>;
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
{ AirflowNetwork_MultiZone_ExternalNodeFields::Name, "Name", "Name"},
{ AirflowNetwork_MultiZone_ExternalNodeFields::ExternalNodeHeight, "ExternalNodeHeight", "External Node Height"},
{ AirflowNetwork_MultiZone_ExternalNodeFields::WindPressureCoefficientCurveName, "WindPressureCoefficientCurveName", "Wind Pressure Coefficient Curve Name"},
{ AirflowNetwork_MultiZone_ExternalNodeFields::SymmetricWindPressureCoefficientCurve, "SymmetricWindPressureCoefficientCurve", "Symmetric Wind Pressure Coefficient Curve"},
{ AirflowNetwork_MultiZone_ExternalNodeFields::WindAngleType, "WindAngleType", "Wind Angle Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_MultiZone_ExternalNodeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_MultiZone_ExternalNodeFields> OptionalAirflowNetwork_MultiZone_ExternalNodeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_MULTIZONE_EXTERNALNODE_FIELDENUMS_HXX
