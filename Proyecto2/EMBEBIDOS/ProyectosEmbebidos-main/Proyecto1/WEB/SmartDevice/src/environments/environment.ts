// This file can be replaced during build by using the `fileReplacements` array.
// `ng build --prod` replaces `environment.ts` with `environment.prod.ts`.
// The list of file replacements can be found in `angular.json`.

export const environment = {
  production: false,
  firebaseConfig : {
    apiKey: "AIzaSyBoZH2ktPYTbE64cjlQpeLAao5noUaKQ84",
    authDomain: "smarthome-d1c82.firebaseapp.com",
    databaseURL: "https://smarthome-d1c82.firebaseio.com",
    projectId: "smarthome-d1c82",
    storageBucket: "smarthome-d1c82.appspot.com",
    messagingSenderId: "1067243925686",
    appId: "1:1067243925686:web:f4147cef64ac4b39567617",
    measurementId: "G-34R5SXK69Z"
  },
	hmr: false,
	http: {
		apiUrl: '<https://api.myweb.com>',
	},
	mqtt: {
		server: 'mqtt.myweb.com',
		protocol: "wss",
		port: 1883
	},
};

/*
 * For easier debugging in development mode, you can import the following file
 * to ignore zone related error stack frames such as `zone.run`, `zoneDelegate.invokeTask`.
 *
 * This import should be commented out in production mode because it will have a negative impact
 * on performance if an error is thrown.
 */
// import 'zone.js/dist/zone-error';  // Included with Angular CLI.
