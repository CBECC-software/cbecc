/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
OutputCSV, OutputMTR, OutputESO, OutputEIO, OutputTabular, OutputSQLite, OutputJSON, OutputAUDIT, OutputZoneSizing, OutputSystemSizing, OutputDXF, OutputBND, OutputRDD, OutputMDD, OutputMTD, OutputEND, OutputSHD, OutputDFS, OutputGLHE, OutputDelightIn, OutputDelightELdmp, OutputDelightDFdmp, OutputEDD, OutputDBG, OutputPerfLog, OutputSLN, OutputSCI, OutputWRL, OutputScreen, OutputExtShd, OutputTarcog,   };
  OutputControl_FilesFields()
   : EnumBase<OutputControl_FilesFields>(OutputCSV) {} 
  OutputControl_FilesFields(const std::string &t_name) 
   : EnumBase<OutputControl_FilesFields>(t_name) {} 
  OutputControl_FilesFields(int t_value) 
   : EnumBase<OutputControl_FilesFields>(t_value) {} 
  static std::string enumName() 
  { return "OutputControl_FilesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OutputControl_FilesFields>::value()); }
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
