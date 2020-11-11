import { NgModule } from '@angular/core';
import { PagesRoutingModule, routedComponents } from './pages-routing.module';

import { ReactiveFormsModule, FormsModule }  from '@angular/forms';
//import { AuthService } from '../services/login.service'; 
import {NgxMqttClientModule} from '../ngx-mqtt-client';
import { MqttModule, IMqttServiceOptions } from "ngx-mqtt";

@NgModule({

  imports: [
    PagesRoutingModule,
    FormsModule,
    ReactiveFormsModule,
    FormsModule
  ],
  providers : [
  //	AuthService
  ],
  declarations: [
    ...routedComponents,
  ]
})
export class PagesModule { }
