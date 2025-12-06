/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OUTPUT_METER_METERFILEONLY_FIELDENUMS_HXX
#define UTILITIES_IDD_OUTPUT_METER_METERFILEONLY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Output_Meter_MeterFileOnlyFields
 *  \brief Enumeration of Output:Meter:MeterFileOnly's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Output_Meter_MeterFileOnlyFields, )
#else
class Output_Meter_MeterFileOnlyFields: public ::EnumBase<Output_Meter_MeterFileOnlyFields> {
 public: 
  enum domain 
  {
KeyName, ReportingFrequency,   };
  Output_Meter_MeterFileOnlyFields()
   : EnumBase<Output_Meter_MeterFileOnlyFields>(KeyName) {} 
  Output_Meter_MeterFileOnlyFields(const std::string &t_name) 
   : EnumBase<Output_Meter_MeterFileOnlyFields>(t_name) {} 
  Output_Meter_MeterFileOnlyFields(int t_value) 
   : EnumBase<Output_Meter_MeterFileOnlyFields>(t_value) {} 
  static std::string enumName() 
  { return "Output_Meter_MeterFileOnlyFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Output_Meter_MeterFileOnlyFields>::integer_value()); }
   private:
    friend class EnumBase<Output_Meter_MeterFileOnlyFields>;
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
{ Output_Meter_MeterFileOnlyFields::KeyName, "KeyName", "Key Name"},
{ Output_Meter_MeterFileOnlyFields::ReportingFrequency, "ReportingFrequency", "Reporting Frequency"},
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
  inline std::ostream &operator<<(std::ostream &os, const Output_Meter_MeterFileOnlyFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Output_Meter_MeterFileOnlyFields> OptionalOutput_Meter_MeterFileOnlyFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OUTPUT_METER_METERFILEONLY_FIELDENUMS_HXX
