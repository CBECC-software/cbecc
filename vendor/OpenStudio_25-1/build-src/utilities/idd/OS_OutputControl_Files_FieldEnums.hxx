/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_OUTPUTCONTROL_FILES_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_OUTPUTCONTROL_FILES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_OutputControl_FilesFields
 *  \brief Enumeration of OS:OutputControl:Files's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_OutputControl_FilesFields, )
#else
class OS_OutputControl_FilesFields: public ::EnumBase<OS_OutputControl_FilesFields> {
 public: 
  enum domain 
  {
Handle, OutputCSV, OutputMTR, OutputESO, OutputEIO, OutputTabular, OutputSQLite, OutputJSON, OutputAUDIT, OutputSpaceSizing, OutputZoneSizing, OutputSystemSizing, OutputDXF, OutputBND, OutputRDD, OutputMDD, OutputMTD, OutputSHD, OutputDFS, OutputGLHE, OutputDelightIn, OutputDelightELdmp, OutputDelightDFdmp, OutputEDD, OutputDBG, OutputPerfLog, OutputSLN, OutputSCI, OutputWRL, OutputScreen, OutputExtShd, OutputTarcog,   };
  OS_OutputControl_FilesFields()
   : EnumBase<OS_OutputControl_FilesFields>(Handle) {} 
  OS_OutputControl_FilesFields(const std::string &t_name) 
   : EnumBase<OS_OutputControl_FilesFields>(t_name) {} 
  OS_OutputControl_FilesFields(int t_value) 
   : EnumBase<OS_OutputControl_FilesFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_OutputControl_FilesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_OutputControl_FilesFields>::integer_value()); }
   private:
    friend class EnumBase<OS_OutputControl_FilesFields>;
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
{ OS_OutputControl_FilesFields::Handle, "Handle", "Handle"},
{ OS_OutputControl_FilesFields::OutputCSV, "OutputCSV", "Output CSV"},
{ OS_OutputControl_FilesFields::OutputMTR, "OutputMTR", "Output MTR"},
{ OS_OutputControl_FilesFields::OutputESO, "OutputESO", "Output ESO"},
{ OS_OutputControl_FilesFields::OutputEIO, "OutputEIO", "Output EIO"},
{ OS_OutputControl_FilesFields::OutputTabular, "OutputTabular", "Output Tabular"},
{ OS_OutputControl_FilesFields::OutputSQLite, "OutputSQLite", "Output SQLite"},
{ OS_OutputControl_FilesFields::OutputJSON, "OutputJSON", "Output JSON"},
{ OS_OutputControl_FilesFields::OutputAUDIT, "OutputAUDIT", "Output AUDIT"},
{ OS_OutputControl_FilesFields::OutputSpaceSizing, "OutputSpaceSizing", "Output Space Sizing"},
{ OS_OutputControl_FilesFields::OutputZoneSizing, "OutputZoneSizing", "Output Zone Sizing"},
{ OS_OutputControl_FilesFields::OutputSystemSizing, "OutputSystemSizing", "Output System Sizing"},
{ OS_OutputControl_FilesFields::OutputDXF, "OutputDXF", "Output DXF"},
{ OS_OutputControl_FilesFields::OutputBND, "OutputBND", "Output BND"},
{ OS_OutputControl_FilesFields::OutputRDD, "OutputRDD", "Output RDD"},
{ OS_OutputControl_FilesFields::OutputMDD, "OutputMDD", "Output MDD"},
{ OS_OutputControl_FilesFields::OutputMTD, "OutputMTD", "Output MTD"},
{ OS_OutputControl_FilesFields::OutputSHD, "OutputSHD", "Output SHD"},
{ OS_OutputControl_FilesFields::OutputDFS, "OutputDFS", "Output DFS"},
{ OS_OutputControl_FilesFields::OutputGLHE, "OutputGLHE", "Output GLHE"},
{ OS_OutputControl_FilesFields::OutputDelightIn, "OutputDelightIn", "Output DelightIn"},
{ OS_OutputControl_FilesFields::OutputDelightELdmp, "OutputDelightELdmp", "Output DelightELdmp"},
{ OS_OutputControl_FilesFields::OutputDelightDFdmp, "OutputDelightDFdmp", "Output DelightDFdmp"},
{ OS_OutputControl_FilesFields::OutputEDD, "OutputEDD", "Output EDD"},
{ OS_OutputControl_FilesFields::OutputDBG, "OutputDBG", "Output DBG"},
{ OS_OutputControl_FilesFields::OutputPerfLog, "OutputPerfLog", "Output PerfLog"},
{ OS_OutputControl_FilesFields::OutputSLN, "OutputSLN", "Output SLN"},
{ OS_OutputControl_FilesFields::OutputSCI, "OutputSCI", "Output SCI"},
{ OS_OutputControl_FilesFields::OutputWRL, "OutputWRL", "Output WRL"},
{ OS_OutputControl_FilesFields::OutputScreen, "OutputScreen", "Output Screen"},
{ OS_OutputControl_FilesFields::OutputExtShd, "OutputExtShd", "Output ExtShd"},
{ OS_OutputControl_FilesFields::OutputTarcog, "OutputTarcog", "Output Tarcog"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_OutputControl_FilesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_OutputControl_FilesFields> OptionalOS_OutputControl_FilesFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_OUTPUTCONTROL_FILES_FIELDENUMS_HXX
