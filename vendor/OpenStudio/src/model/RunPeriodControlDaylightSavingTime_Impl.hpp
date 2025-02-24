/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef MODEL_RUNPERIODCONTROLDAYLIGHTSAVINGTIME_IMPL_HPP
#define MODEL_RUNPERIODCONTROLDAYLIGHTSAVINGTIME_IMPL_HPP

#include "ModelAPI.hpp"
#include "ModelObject_Impl.hpp"

namespace openstudio {

class Date;
class MonthOfYear;
class NthDayOfWeekInMonth;
class DayOfWeek;

namespace model {

  namespace detail {

    /** RunPeriodControlDaylightSavingTime_Impl is a ModelObject_Impl that is the implementation class for RunPeriodControlDaylightSavingTime.*/
    class MODEL_API RunPeriodControlDaylightSavingTime_Impl : public ModelObject_Impl
    {
     public:
      /** @name Constructors and Destructors */
      //@{

      RunPeriodControlDaylightSavingTime_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

      RunPeriodControlDaylightSavingTime_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);

      RunPeriodControlDaylightSavingTime_Impl(const RunPeriodControlDaylightSavingTime_Impl& other, Model_Impl* model, bool keepHandle);

      virtual ~RunPeriodControlDaylightSavingTime_Impl() {}

      //@}

      virtual boost::optional<ParentObject> parent() const override;

      virtual bool setParent(ParentObject& newParent) override;

      virtual const std::vector<std::string>& outputVariableNames() const override;

      virtual IddObjectType iddObjectType() const override;

      /** @name Getters */
      //@{

      openstudio::Date startDate() const;

      boost::optional<openstudio::NthDayOfWeekInMonth> startNthDayOfWeekInMonth() const;

      openstudio::Date endDate() const;

      boost::optional<openstudio::NthDayOfWeekInMonth> endNthDayOfWeekInMonth() const;

      //@}
      /** @name Setters */
      //@{

      bool setStartDate(const std::string& startDate);
      bool setStartDate(const openstudio::MonthOfYear& monthOfYear, unsigned day);
      bool setStartDate(const openstudio::NthDayOfWeekInMonth& nth, const openstudio::DayOfWeek& dayOfWeek,
                        const openstudio::MonthOfYear& monthOfYear);

      bool setEndDate(const std::string& endDate);
      bool setEndDate(const openstudio::MonthOfYear& monthOfYear, unsigned day);
      bool setEndDate(const openstudio::NthDayOfWeekInMonth& nth, const openstudio::DayOfWeek& dayOfWeek, const openstudio::MonthOfYear& monthOfYear);

      // ensure that this object does not contain the date 2/29
      void ensureNoLeapDays();

      //@}
     protected:
     private:
      openstudio::Date getDate(const std::string& text) const;

      boost::optional<openstudio::NthDayOfWeekInMonth> getNthDayOfWeekInMonth(const std::string& text) const;

      REGISTER_LOGGER("openstudio.model.RunPeriodControlDaylightSavingTime");
    };

  }  // namespace detail

}  // namespace model
}  // namespace openstudio

#endif  // MODEL_RUNPERIODCONTROLDAYLIGHTSAVINGTIME_IMPL_HPP
