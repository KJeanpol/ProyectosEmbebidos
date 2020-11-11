import { NgModule } from '@angular/core';
import { AuthRoutingModule, routedComponents } from './auth-routing.module';

import { ReactiveFormsModule, FormsModule }  from '@angular/forms';
//import { AuthService } from '../services/login.service'; 

@NgModule({
  imports: [
    AuthRoutingModule,
    FormsModule,
    ReactiveFormsModule
  ],
  providers : [
  //	AuthService
  ],
  declarations: [
    ...routedComponents,
  ]
})
export class AuthModule { }
