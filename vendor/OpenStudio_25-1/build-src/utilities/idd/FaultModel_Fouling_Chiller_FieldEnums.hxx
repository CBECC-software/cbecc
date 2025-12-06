/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_FAULTMODEL_FOULING_CHILLER_FIELDENUMS_HXX
#define UTILITIES_IDD_FAULTMODEL_FOULING_CHILLER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FaultModel_Fouling_ChillerFields
 *  \brief Enumeration of FaultModel:Fouling:Chiller's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FaultModel_Fouling_ChillerFields, )
#else
class FaultModel_Fouling_ChillerFields: public ::EnumBase<FaultModel_Fouling_ChillerFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, SeverityScheduleName, ChillerObjectType, ChillerObjectName, FoulingFactor,   };
  FaultModel_Fouling_ChillerFields()
   : EnumBase<FaultModel_Fouling_ChillerFields>(Name) {} 
  FaultModel_Fouling_ChillerFields(const std::string &t_name) 
   : EnumBase<FaultModel_Fouling_ChillerFields>(t_name) {} 
  FaultModel_Fouling_ChillerFields(int t_value) 
   : EnumBase<FaultModel_Fouling_ChillerFields>(t_value) {} 
  static std::string enumName() 
  { return "FaultModel_Fouling_ChillerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FaultModel_Fouling_ChillerFields>::integer_value()); }
   private:
    friend class EnumBase<FaultModel_Fouling_ChillerFields>;
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
{ FaultModel_Fouling_ChillerFields::Name, "Name", "Name"},
{ FaultModel_Fouling_ChillerFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ FaultModel_Fouling_ChillerFields::SeverityScheduleName, "SeverityScheduleName", "Severity Schedule Name"},
{ FaultModel_Fouling_ChillerFields::ChillerObjectType, "ChillerObjectType", "Chiller Object Type"},
{ FaultModel_Fouling_ChillerFields::ChillerObjectName, "ChillerObjectName", "Chiller Object Name"},
{ FaultModel_Fouling_ChillerFields::FoulingFactor, "FoulingFactor", "Fouling Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const FaultModel_Fouling_ChillerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FaultModel_Fouling_ChillerFields> OptionalFaultModel_Fouling_ChillerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FAULTMODEL_FOULING_CHILLER_FIELDENUMS_HXX
