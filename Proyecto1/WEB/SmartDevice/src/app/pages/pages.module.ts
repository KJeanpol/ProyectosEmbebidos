import { NgModule } from '@angular/core';
import { PagesRoutingModule, routedComponents } from './pages-routing.module';

import { ReactiveFormsModule, FormsModule }  from '@angular/forms';
//import { AuthService } from '../services/login.service'; 
import {NgxMqttClientModule} from '../ngx-mqtt-client';
@NgModule({

  imports: [
    PagesRoutingModule,
    FormsModule,
    ReactiveFormsModule,
    NgxMqttClientModule.withOptions({
      host: 'test.mosquitto.org',
      protocol: 'ws',
      port: 8080,
      path: '/CoreElectronics',
      keepalive: 5
  })
  ],
  providers : [
  //	AuthService
  ],
  declarations: [
    ...routedComponents,
  ]
})
export class PagesModule { }
