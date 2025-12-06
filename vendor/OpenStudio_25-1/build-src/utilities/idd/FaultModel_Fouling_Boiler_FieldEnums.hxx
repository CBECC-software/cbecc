/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_FAULTMODEL_FOULING_BOILER_FIELDENUMS_HXX
#define UTILITIES_IDD_FAULTMODEL_FOULING_BOILER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FaultModel_Fouling_BoilerFields
 *  \brief Enumeration of FaultModel:Fouling:Boiler's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FaultModel_Fouling_BoilerFields, )
#else
class FaultModel_Fouling_BoilerFields: public ::EnumBase<FaultModel_Fouling_BoilerFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, SeverityScheduleName, BoilerObjectType, BoilerObjectName, FoulingFactor,   };
  FaultModel_Fouling_BoilerFields()
   : EnumBase<FaultModel_Fouling_BoilerFields>(Name) {} 
  FaultModel_Fouling_BoilerFields(const std::string &t_name) 
   : EnumBase<FaultModel_Fouling_BoilerFields>(t_name) {} 
  FaultModel_Fouling_BoilerFields(int t_value) 
   : EnumBase<FaultModel_Fouling_BoilerFields>(t_value) {} 
  static std::string enumName() 
  { return "FaultModel_Fouling_BoilerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FaultModel_Fouling_BoilerFields>::integer_value()); }
   private:
    friend class EnumBase<FaultModel_Fouling_BoilerFields>;
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
{ FaultModel_Fouling_BoilerFields::Name, "Name", "Name"},
{ FaultModel_Fouling_BoilerFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ FaultModel_Fouling_BoilerFields::SeverityScheduleName, "SeverityScheduleName", "Severity Schedule Name"},
{ FaultModel_Fouling_BoilerFields::BoilerObjectType, "BoilerObjectType", "Boiler Object Type"},
{ FaultModel_Fouling_BoilerFields::BoilerObjectName, "BoilerObjectName", "Boiler Object Name"},
{ FaultModel_Fouling_BoilerFields::FoulingFactor, "FoulingFactor", "Fouling Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const FaultModel_Fouling_BoilerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FaultModel_Fouling_BoilerFields> OptionalFaultModel_Fouling_BoilerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FAULTMODEL_FOULING_BOILER_FIELDENUMS_HXX
