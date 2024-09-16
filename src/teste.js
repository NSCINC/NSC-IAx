const axios = require('axios');
const expect = require('chai').expect;

const baseURL = 'http://localhost:8080';

describe('HoloFi DApp API Tests', function() {

    it('should add an investment plan successfully', async function() {
        const plan = {
            plan_name: 'testPlan',
            initial_investment: 1000,
            monthly_return: 10,
            annual_return: 120,
            net_annual_return: 600,
            slots: 1000
        };
        try {
            const response = await axios.post(`${baseURL}/add-plan`, plan);
            expect(response.status).to.equal(200);
            expect(response.data.message).to.equal('Plan added successfully!');
        } catch (error) {
            throw new Error('Failed to add investment plan: ' + (error.response ? error.response.data : error.message));
        }
    });

    it('should invest in a plan successfully', async function() {
        const investment = {
            plan_name: 'testPlan',
            amount: 500,
            investor_address: '0x4444444444444444444444444444444444444444'
        };
        try {
            const response = await axios.post(`${baseURL}/invest`, investment);
            expect(response.status).to.equal(200);
            expect(response.data.message).to.equal('Investment completed successfully!');
        } catch (error) {
            throw new Error('Failed to invest: ' + (error.response ? error.response.data : error.message));
        }
    });

    it('should authenticate a message successfully', async function() {
        const messageHash = '0xabcdef1234567890abcdef1234567890abcdef1234567890abcdef1234567890';
        try {
            const response = await axios.post(`${baseURL}/authenticate-message`, { message_hash: messageHash });
            expect(response.status).to.equal(200);
            expect(response.data.message).to.equal('Message authenticated successfully!');
        } catch (error) {
            throw new Error('Failed to authenticate message: ' + (error.response ? error.response.data : error.message));
        }
    });

});
