/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_REFRIGERATION_COMPRESSOR_FIELDENUMS_HXX
#define UTILITIES_IDD_REFRIGERATION_COMPRESSOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Refrigeration_CompressorFields
 *  \brief Enumeration of Refrigeration:Compressor's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Refrigeration_CompressorFields, )
#else
class Refrigeration_CompressorFields: public ::EnumBase<Refrigeration_CompressorFields> {
 public: 
  enum domain 
  {
Name, RefrigerationCompressorPowerCurveName, RefrigerationCompressorCapacityCurveName, RatedSuperheat, RatedReturnGasTemperature, RatedLiquidTemperature, RatedSubcooling, EndUseSubcategory, ModeofOperation, TranscriticalCompressorPowerCurveName, TranscriticalCompressorCapacityCurveName,   };
  Refrigeration_CompressorFields()
   : EnumBase<Refrigeration_CompressorFields>(Name) {} 
  Refrigeration_CompressorFields(const std::string &t_name) 
   : EnumBase<Refrigeration_CompressorFields>(t_name) {} 
  Refrigeration_CompressorFields(int t_value) 
   : EnumBase<Refrigeration_CompressorFields>(t_value) {} 
  static std::string enumName() 
  { return "Refrigeration_CompressorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Refrigeration_CompressorFields>::value()); }
   private:
    friend class EnumBase<Refrigeration_CompressorFields>;
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
{ Refrigeration_CompressorFields::Name, "Name", "Name"},
{ Refrigeration_CompressorFields::RefrigerationCompressorPowerCurveName, "RefrigerationCompressorPowerCurveName", "Refrigeration Compressor Power Curve Name"},
{ Refrigeration_CompressorFields::RefrigerationCompressorCapacityCurveName, "RefrigerationCompressorCapacityCurveName", "Refrigeration Compressor Capacity Curve Name"},
{ Refrigeration_CompressorFields::RatedSuperheat, "RatedSuperheat", "Rated Superheat"},
{ Refrigeration_CompressorFields::RatedReturnGasTemperature, "RatedReturnGasTemperature", "Rated Return Gas Temperature"},
{ Refrigeration_CompressorFields::RatedLiquidTemperature, "RatedLiquidTemperature", "Rated Liquid Temperature"},
{ Refrigeration_CompressorFields::RatedSubcooling, "RatedSubcooling", "Rated Subcooling"},
{ Refrigeration_CompressorFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ Refrigeration_CompressorFields::ModeofOperation, "ModeofOperation", "Mode of Operation"},
{ Refrigeration_CompressorFields::TranscriticalCompressorPowerCurveName, "TranscriticalCompressorPowerCurveName", "Transcritical Compressor Power Curve Name"},
{ Refrigeration_CompressorFields::TranscriticalCompressorCapacityCurveName, "TranscriticalCompressorCapacityCurveName", "Transcritical Compressor Capacity Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Refrigeration_CompressorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Refrigeration_CompressorFields> OptionalRefrigeration_CompressorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_REFRIGERATION_COMPRESSOR_FIELDENUMS_HXX
