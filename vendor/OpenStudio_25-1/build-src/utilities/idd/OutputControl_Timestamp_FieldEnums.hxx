/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OUTPUTCONTROL_TIMESTAMP_FIELDENUMS_HXX
#define UTILITIES_IDD_OUTPUTCONTROL_TIMESTAMP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OutputControl_TimestampFields
 *  \brief Enumeration of OutputControl:Timestamp's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OutputControl_TimestampFields, )
#else
class OutputControl_TimestampFields: public ::EnumBase<OutputControl_TimestampFields> {
 public: 
  enum domain 
  {
ISO8601Format, TimestampatBeginningofInterval,   };
  OutputControl_TimestampFields()
   : EnumBase<OutputControl_TimestampFields>(ISO8601Format) {} 
  OutputControl_TimestampFields(const std::string &t_name) 
   : EnumBase<OutputControl_TimestampFields>(t_name) {} 
  OutputControl_TimestampFields(int t_value) 
   : EnumBase<OutputControl_TimestampFields>(t_value) {} 
  static std::string enumName() 
  { return "OutputControl_TimestampFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OutputControl_TimestampFields>::integer_value()); }
   private:
    friend class EnumBase<OutputControl_TimestampFields>;
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
{ OutputControl_TimestampFields::ISO8601Format, "ISO8601Format", "ISO 8601 Format"},
{ OutputControl_TimestampFields::TimestampatBeginningofInterval, "TimestampatBeginningofInterval", "Timestamp at Beginning of Interval"},
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
  inline std::ostream &operator<<(std::ostream &os, const OutputControl_TimestampFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OutputControl_TimestampFields> OptionalOutputControl_TimestampFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OUTPUTCONTROL_TIMESTAMP_FIELDENUMS_HXX
