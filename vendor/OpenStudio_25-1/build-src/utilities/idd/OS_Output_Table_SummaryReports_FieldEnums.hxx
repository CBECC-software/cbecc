/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_OUTPUT_TABLE_SUMMARYREPORTS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_OUTPUT_TABLE_SUMMARYREPORTS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Output_Table_SummaryReportsFields
 *  \brief Enumeration of OS:Output:Table:SummaryReports's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Output_Table_SummaryReportsFields, )
#else
class OS_Output_Table_SummaryReportsFields: public ::EnumBase<OS_Output_Table_SummaryReportsFields> {
 public: 
  enum domain 
  {
Handle,   };
  OS_Output_Table_SummaryReportsFields()
   : EnumBase<OS_Output_Table_SummaryReportsFields>(Handle) {} 
  OS_Output_Table_SummaryReportsFields(const std::string &t_name) 
   : EnumBase<OS_Output_Table_SummaryReportsFields>(t_name) {} 
  OS_Output_Table_SummaryReportsFields(int t_value) 
   : EnumBase<OS_Output_Table_SummaryReportsFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Output_Table_SummaryReportsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Output_Table_SummaryReportsFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Output_Table_SummaryReportsFields>;
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
{ OS_Output_Table_SummaryReportsFields::Handle, "Handle", "Handle"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Output_Table_SummaryReportsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Output_Table_SummaryReportsFields> OptionalOS_Output_Table_SummaryReportsFields ;
#endif

/** \class OS_Output_Table_SummaryReportsExtensibleFields
 *  \brief Enumeration of OS:Output:Table:SummaryReports's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Output_Table_SummaryReportsExtensibleFields, )
#else
class OS_Output_Table_SummaryReportsExtensibleFields: public ::EnumBase<OS_Output_Table_SummaryReportsExtensibleFields> {
 public: 
  enum domain 
  {
ReportName,   };
  OS_Output_Table_SummaryReportsExtensibleFields()
   : EnumBase<OS_Output_Table_SummaryReportsExtensibleFields>(ReportName) {} 
  OS_Output_Table_SummaryReportsExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Output_Table_SummaryReportsExtensibleFields>(t_name) {} 
  OS_Output_Table_SummaryReportsExtensibleFields(int t_value) 
   : EnumBase<OS_Output_Table_SummaryReportsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Output_Table_SummaryReportsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Output_Table_SummaryReportsExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Output_Table_SummaryReportsExtensibleFields>;
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
{ OS_Output_Table_SummaryReportsExtensibleFields::ReportName, "ReportName", "Report Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Output_Table_SummaryReportsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Output_Table_SummaryReportsExtensibleFields> OptionalOS_Output_Table_SummaryReportsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_OUTPUT_TABLE_SUMMARYREPORTS_FIELDENUMS_HXX
