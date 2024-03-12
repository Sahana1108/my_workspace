// Google Pay implementation using Javascript. (Based on Tutorial 6)

// 1: Define version
const baseRequest = {
  apiVersion: 2,
  apiVersionMinor: 0
};

// 2: Request payment token
const tokenizationSpecification = {
  type: 'PAYMENT_GATEWAY',
  parameters: {
    'gateway': 'example',
    'gatewayMerchantId': 'exampleGatewayMerchantId'
  }
};

// 3: Define supported card networks
const allowedCardNetworks = ["AMEX", "DISCOVER", "INTERAC", "JCB", "MASTERCARD", "VISA"];

const allowedCardAuthMethods = ["PAN_ONLY", "CRYPTOGRAM_3DS"];

// 4: Describe allowed payment methods
const baseCardPaymentMethod = {
  type: 'CARD',
  parameters: {
    allowedAuthMethods: allowedCardAuthMethods,
    allowedCardNetworks: allowedCardNetworks
  }
};

const cardPaymentMethod = Object.assign(
  {tokenizationSpecification: tokenizationSpecification},
  baseCardPaymentMethod
);

// 5: Load Google Pay API Javascript library
let paymentsClient = null;
function getGooglePaymentsClient() {
	if ( paymentsClient === null ) {
		paymentsClient = new google.payments.api.PaymentsClient({
			environment: 'TEST',
			paymentDataCallbacks: {
				onPaymentAuthorized: onPaymentAuthorized
			}
		});
	}
	return paymentsClient;
}

// 6: Determine readiness to pay
function getGoogleIsReadyToPayRequest() {
	return Object.assign(
		{},
		baseRequest,
		{
			allowedPaymentMethods: [baseCardPaymentMethod]
		}
	);
}

function onGooglePayLoaded() {
	const paymentsClient = getGooglePaymentsClient();
	paymentsClient.isReadyToPay(getGoogleIsReadyToPayRequest())
		.then(function(response) {
		if (response.result) {
			addGooglePayButton();
		}
	})
		.catch(function(err) {
		// show error in developer console for debugging
		console.error(err);
	});
}

// 7: Add payment button
function addGooglePayButton() {
	const paymentsClient = getGooglePaymentsClient();
	const button = paymentsClient.createButton({
		onClick: onGooglePaymentButtonClicked,
		allowedPaymentMethods: [baseCardPaymentMethod]
	});
	document.getElementById('container').appendChild(button);
}

// 8: Create PaymentDataRequest object
function getGooglePaymentDataRequest() {
	const paymentDataRequest = Object.assign({}, baseRequest);
	paymentDataRequest.allowedPaymentMethods = [cardPaymentMethod];
	paymentDataRequest.transactionInfo = getGoogleTransactionInfo();
	paymentDataRequest.merchantInfo = {
		merchantId: '12345678901234567890',
		merchantName: 'Example Merchant'
	};
	paymentDataRequest.callbackIntents = ["PAYMENT_AUTHORIZATION"];
	return paymentDataRequest;
}

function getGoogleTransactionInfo() {
  return {
    displayItems: [
      {
        label: "Subtotal",
        type: "SUBTOTAL",
        price: "1.00",
      },
      {
        label: "Tax",
        type: "TAX",
        price: "0.00",
      }
    ],
    countryCode: 'AU',
    currencyCode: "AUD",
    totalPriceStatus: "FINAL",
    totalPrice: "1.00",
    totalPriceLabel: "Total"
  };
}

// 9: Register event handler for user gestures
function onGooglePaymentButtonClicked() {
	const paymentDataRequest = getGooglePaymentDataRequest();
	paymentDataRequest.transactionInfo = getGoogleTransactionInfo();
	const paymentsClient = getGooglePaymentsClient();
	paymentsClient.loadPaymentData(paymentDataRequest)
		.then(function(paymentData) {
		processPayment(paymentData);
	}).catch(function(err) {
		console.error(err);
	});
}

// 10: Set up Authorise Payments
function onPaymentAuthorized(paymentData) {
	return new Promise(function(resolve, reject){
		processPayment(paymentData)
			.then(function() {
			resolve({transactionState: 'SUCCESS'});
		}).catch(function() {
			resolve({transactionState: 'ERROR',
					 error: {
						 intent: 'PAYMENT_AUTHORIZATION',
						 message: 'Insufficient funds',
						 reason: 'PAYMENT_DATA_INVALID'
					 }
					});
		});
	});
}

// 11: Process payment data returned by the API
let attempts = 0;
function processPayment(paymentData) {
	return new Promise(function(resolve, reject) {
		setTimeout(function() {
			paymentToken = paymentData.paymentMethodData.tokenizationData.token;
			if (attempts++ % 2 == 0) {
				reject(new Error('Every other attempt fails, next one should succeed'));
			} else {
				resolve({});
			}
		}, 500);
	});
}

