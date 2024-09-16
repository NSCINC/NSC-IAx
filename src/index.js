import React, { useState } from 'react';

const InvestmentPlanForm = ({ onAddPlan }) => {
  const [planName, setPlanName] = useState('');
  const [initialInvestment, setInitialInvestment] = useState('');
  const [monthlyReturn, setMonthlyReturn] = useState('');
  const [annualReturn, setAnnualReturn] = useState('');
  const [netAnnualReturn, setNetAnnualReturn] = useState('');
  const [slots, setSlots] = useState('');

  const handleSubmit = (e) => {
    e.preventDefault();
    const plan = {
      plan_name: planName,
      initial_investment: initialInvestment,
      monthly_return: monthlyReturn,
      annual_return: annualReturn,
      net_annual_return: netAnnualReturn,
      slots: slots
    };
    onAddPlan(plan);
  };

  return (
    <form onSubmit={handleSubmit}>
      <h2>Add Investment Plan</h2>
      <input 
        type="text" 
        value={planName} 
        onChange={(e) => setPlanName(e.target.value)} 
        placeholder="Plan Name" 
        required 
      />
      <input 
        type="number" 
        value={initialInvestment} 
        onChange={(e) => setInitialInvestment(e.target.value)} 
        placeholder="Initial Investment" 
        required 
      />
      <input 
        type="number" 
        value={monthlyReturn} 
        onChange={(e) => setMonthlyReturn(e.target.value)} 
        placeholder="Monthly Return (%)" 
        required 
      />
      <input 
        type="number" 
        value={annualReturn} 
        onChange={(e) => setAnnualReturn(e.target.value)} 
        placeholder="Annual Return (%)" 
        required 
      />
      <input 
        type="number" 
        value={netAnnualReturn} 
        onChange={(e) => setNetAnnualReturn(e.target.value)} 
        placeholder="Net Annual Return (%)" 
        required 
      />
      <input 
        type="number" 
        value={slots} 
        onChange={(e) => setSlots(e.target.value)} 
        placeholder="Slots Available" 
        required 
      />
      <button type="submit">Add Plan</button>
    </form>
  );
};

export default InvestmentPlanForm;
import React from 'react';

const InvestmentPlanList = ({ plans }) => {
  return (
    <div>
      <h2>Investment Plans</h2>
      <ul>
        {plans.map((plan, index) => (
          <li key={index}>
            <strong>{plan.plan_name}</strong>: 
            Initial Investment: {plan.initial_investment}, 
            Monthly Return: {plan.monthly_return}%, 
            Annual Return: {plan.annual_return}%, 
            Net Annual Return: {plan.net_annual_return}%, 
            Slots: {plan.slots}
          </li>
        ))}
      </ul>
    </div>
  );
};

export default InvestmentPlanList;
import React from 'react';

const InvestmentPlanList = ({ plans }) => {
  return (
    <div>
      <h2>Investment Plans</h2>
      <ul>
        {plans.map((plan, index) => (
          <li key={index}>
            <strong>{plan.plan_name}</strong>: 
            Initial Investment: {plan.initial_investment}, 
            Monthly Return: {plan.monthly_return}%, 
            Annual Return: {plan.annual_return}%, 
            Net Annual Return: {plan.net_annual_return}%, 
            Slots: {plan.slots}
          </li>
        ))}
      </ul>
    </div>
  );
};

export default InvestmentPlanList;
import React, { useState } from 'react';
import InvestmentPlanForm from './components/InvestmentPlanForm';
import InvestmentPlanList from './components/InvestmentPlanList';
import './App.css';

const App = () => {
  const [plans, setPlans] = useState([]);

  const handleAddPlan = (plan) => {
    setPlans([...plans, plan]);
  };

  return (
    <div className="container">
      <header>
        <h1>Hollow Engine Investment Management</h1>
      </header>
      <InvestmentPlanForm onAddPlan={handleAddPlan} />
      <InvestmentPlanList plans={plans} />
    </div>
  );
};

export default App;
const handleAddPlan = async (plan) => {
    try {
      const response = await fetch('http://localhost:8000/api/plans', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(plan),
      });
      if (response.ok) {
        const newPlan = await response.json();
        setPlans([...plans, newPlan]);
      } else {
        console.error('Failed to add plan');
      }
    } catch (error) {
      console.error('Error:', error);
    }
  };
  