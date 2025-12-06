/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OUTPUTCONTROL_FILES_FIELDENUMS_HXX
#define UTILITIES_IDD_OUTPUTCONTROL_FILES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OutputControl_FilesFields
 *  \brief Enumeration of OutputControl:Files's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OutputControl_FilesFields, )
#else
class OutputControl_FilesFields: public ::EnumBase<OutputControl_FilesFields> {
 public: 
  enum domain 
  {
OutputCSV, OutputMTR, OutputESO, OutputEIO, OutputTabular, OutputSQLite, OutputJSON, OutputAUDIT, OutputSpaceSizing, OutputZoneSizing, OutputSystemSizing, OutputDXF, OutputBND, OutputRDD, OutputMDD, OutputMTD, OutputEND, OutputSHD, OutputDFS, OutputGLHE, OutputDelightIn, OutputDelightELdmp, OutputDelightDFdmp, OutputEDD, OutputDBG, OutputPerfLog, OutputSLN, OutputSCI, OutputWRL, OutputScreen, OutputExtShd, OutputTarcog,   };
  OutputControl_FilesFields()
   : EnumBase<OutputControl_FilesFields>(OutputCSV) {} 
  OutputControl_FilesFields(const std::string &t_name) 
   : EnumBase<OutputControl_FilesFields>(t_name) {} 
  OutputControl_FilesFields(int t_value) 
   : EnumBase<OutputControl_FilesFields>(t_value) {} 
  static std::string enumName() 
  { return "OutputControl_FilesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OutputControl_FilesFields>::integer_value()); }
   private:
    friend class EnumBase<OutputControl_FilesFields>;
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
{ OutputControl_FilesFields::OutputCSV, "OutputCSV", "Output CSV"},
{ OutputControl_FilesFields::OutputMTR, "OutputMTR", "Output MTR"},
{ OutputControl_FilesFields::OutputESO, "OutputESO", "Output ESO"},
{ OutputControl_FilesFields::OutputEIO, "OutputEIO", "Output EIO"},
{ OutputControl_FilesFields::OutputTabular, "OutputTabular", "Output Tabular"},
{ OutputControl_FilesFields::OutputSQLite, "OutputSQLite", "Output SQLite"},
{ OutputControl_FilesFields::OutputJSON, "OutputJSON", "Output JSON"},
{ OutputControl_FilesFields::OutputAUDIT, "OutputAUDIT", "Output AUDIT"},
{ OutputControl_FilesFields::OutputSpaceSizing, "OutputSpaceSizing", "Output Space Sizing"},
{ OutputControl_FilesFields::OutputZoneSizing, "OutputZoneSizing", "Output Zone Sizing"},
{ OutputControl_FilesFields::OutputSystemSizing, "OutputSystemSizing", "Output System Sizing"},
{ OutputControl_FilesFields::OutputDXF, "OutputDXF", "Output DXF"},
{ OutputControl_FilesFields::OutputBND, "OutputBND", "Output BND"},
{ OutputControl_FilesFields::OutputRDD, "OutputRDD", "Output RDD"},
{ OutputControl_FilesFields::OutputMDD, "OutputMDD", "Output MDD"},
{ OutputControl_FilesFields::OutputMTD, "OutputMTD", "Output MTD"},
{ OutputControl_FilesFields::OutputEND, "OutputEND", "Output END"},
{ OutputControl_FilesFields::OutputSHD, "OutputSHD", "Output SHD"},
{ OutputControl_FilesFields::OutputDFS, "OutputDFS", "Output DFS"},
{ OutputControl_FilesFields::OutputGLHE, "OutputGLHE", "Output GLHE"},
{ OutputControl_FilesFields::OutputDelightIn, "OutputDelightIn", "Output DelightIn"},
{ OutputControl_FilesFields::OutputDelightELdmp, "OutputDelightELdmp", "Output DelightELdmp"},
{ OutputControl_FilesFields::OutputDelightDFdmp, "OutputDelightDFdmp", "Output DelightDFdmp"},
{ OutputControl_FilesFields::OutputEDD, "OutputEDD", "Output EDD"},
{ OutputControl_FilesFields::OutputDBG, "OutputDBG", "Output DBG"},
{ OutputControl_FilesFields::OutputPerfLog, "OutputPerfLog", "Output PerfLog"},
{ OutputControl_FilesFields::OutputSLN, "OutputSLN", "Output SLN"},
{ OutputControl_FilesFields::OutputSCI, "OutputSCI", "Output SCI"},
{ OutputControl_FilesFields::OutputWRL, "OutputWRL", "Output WRL"},
{ OutputControl_FilesFields::OutputScreen, "OutputScreen", "Output Screen"},
{ OutputControl_FilesFields::OutputExtShd, "OutputExtShd", "Output ExtShd"},
{ OutputControl_FilesFields::OutputTarcog, "OutputTarcog", "Output Tarcog"},
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
  inline std::ostream &operator<<(std::ostream &os, const OutputControl_FilesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OutputControl_FilesFields> OptionalOutputControl_FilesFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OUTPUTCONTROL_FILES_FIELDENUMS_HXX
